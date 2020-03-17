// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "TcpClient.h"

//#include "muduo/base/Logging.h"
#include "Connector.h"
//#include "EventLoop.h"
//#include "muduo/net/SocketsOps.h"
#include "eventloop.h"
#include "some_func.h"

#include <stdio.h>  // snprintf
#include <functional>



//using namespace muduo;
//using namespace muduo::net;

using namespace evproto; 
using namespace std::placeholders;

// TcpClient::TcpClient(EventLoop* loop)
//   : loop_(loop)
// {
// }

// TcpClient::TcpClient(EventLoop* loop, const string& host, uint16_t port)
//   : loop_(CHECK_NOTNULL(loop)),
//     serverAddr_(host, port)
// {
// }


namespace evproto
{
namespace detail
{

void removeConnection(EventLoop* loop, const TcpConnectionPtr& conn)
{
  loop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
}

void removeConnector(const ConnectorPtr& connector)
{
  //connector->
}

}  // namespace detail
}  // namespace net


TcpClient::TcpClient(EventLoop* loop,
                     //const InetAddress& serverAddr,
		     const sockaddr_in& serverAddr,
                     const string& nameArg)
  : loop_(loop),
    connector_(new Connector(loop, serverAddr)),
    name_(nameArg),
    connectionCallback_(defaultConnectionCallback),
    messageCallback_(defaultMessageCallback),
//    messageCallback_(defaultMessageCallback2),
    retry_(false),
    connect_(true),
    nextConnId_(1)
{
  connector_->setNewConnectionCallback(
      std::bind(&TcpClient::newConnection, this, _1));
  // FIXME setConnectFailedCallback
  cout << "TcpClient::TcpClient[" << name_
           << "] - connector " << get_pointer(connector_) << endl;
}

TcpClient::~TcpClient()
{

  cout << "TcpClient::~TcpClient[" << name_
           << "] - connector " << get_pointer(connector_);
  TcpConnectionPtr conn;
  bool unique = false;
  {
    MutexLockGuard lock(mutex_);
    unique = connection_.unique();
    conn = connection_;
  }
  if (conn)
  {
    assert(loop_ == conn->getLoop());
    // FIXME: not 100% safe, if we are in different thread
    CloseCallback cb = std::bind(&detail::removeConnection, loop_, _1);
    loop_->runInLoop(
        std::bind(&TcpConnection::setCloseCallback, conn, cb));
    if (unique)
    {
      conn->forceClose();
    }
  }
  else
  {
    connector_->stop();
    // FIXME: HACK
 //   loop_->runAfter(1, std::bind(&detail::removeConnector, connector_));
  }

}

void TcpClient::connect()
{
  // FIXME: check state
 // LOG_INFO << "TcpClient::connect[" << name_ << "] - connecting to "
   //        << connector_->serverAddress().toIpPort();

  cout<<"TcpClient::connect"<<endl;
  connect_ = true;
  connector_->start();
}

void TcpClient::disconnect()
{
  connect_ = false;

  {
    MutexLockGuard lock(mutex_);
    if (connection_)
    {
      connection_->shutdown();
    }
  }
}

void TcpClient::stop()
{
  connect_ = false;
  connector_->stop();
}

void TcpClient::newConnection(int sockfd)
{
  //cout<<"--------------C.New.C.New.C.NEW------------------"<<endl;
  loop_->assertInLoopThread();

  struct sockaddr_in peerAddr(getPeerAddr(sockfd));

 // InetAddress peerAddr(sockets::getPeerAddr(sockfd));
//  char buf[32];
char* buf;
 // snprintf(buf, sizeof buf, ":%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
  
  sprintf(buf,"%d",rand());
  ++nextConnId_;
  string connName = name_ + buf; //+ buf;

    struct sockaddr_in localAddr(getLocalAddr(sockfd));
//  InetAddress localAddr(sockets::getLocalAddr(sockfd));
  //  InetAddress localAddr(getLocalAddr(sockfd));
  // FIXME poll with zero timeout to double confirm the new connection
  // FIXME use make_shared if necessary
  TcpConnectionPtr conn(new TcpConnection(loop_,
                                          connName,
                                          sockfd,
                                          localAddr,
                                          peerAddr));


  cout<<"2020------S.E.T.tcpConnectionPtr.-----2020"<<endl;

  conn->setConnectionCallback(connectionCallback_);
  conn->setMessageCallback(messageCallback_);
  conn->setWriteCompleteCallback(writeCompleteCallback_);
  conn->setCloseCallback(
      std::bind(&TcpClient::removeConnection, this, _1)); // FIXME: unsafe
  {
    MutexLockGuard lock(mutex_);
    connection_ = conn;
  }
  conn->connectEstablished();

}

void TcpClient::removeConnection(const TcpConnectionPtr& conn)
{
  loop_->assertInLoopThread();
  assert(loop_ == conn->getLoop());

  {
    MutexLockGuard lock(mutex_);
    assert(connection_ == conn);
    connection_.reset();
  }

  loop_->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
  if (retry_ && connect_)
  {
  //  cout << "TcpClient::connect[" << name_ << "] - Reconnecting to "
    //         << connector_->serverAddress().toIpPort();
    connector_->restart();
  }
}


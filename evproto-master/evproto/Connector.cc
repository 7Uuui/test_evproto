// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
/*
#include "muduo/net/Connector.h"

#include "muduo/base/Logging.h"
#include "muduo/net/Channel.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/SocketsOps.h"
*/
#include "Connector.h"
#include "Channel.h"
#include "eventloop.h"
#include "some_func.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace evproto;
//using namespace muduo::net;

const int Connector::kMaxRetryDelayMs;


Connector::Connector(EventLoop* loop,const sockaddr_in& serverAddr)
//Connector::Connector(EventLoop* loop, const InetAddress& serverAddr)
  : loop_(loop),
    serverAddr_(serverAddr),
    connect_(false),
    state_(kDisconnected),
    retryDelayMs_(kInitRetryDelayMs)
{
//  LOG_DEBUG << "ctor[" << this << "]";
}

Connector::~Connector()
{
 // LOG_DEBUG << "dtor[" << this << "]";
  assert(!channel_);
}

void Connector::start()
{
//  cout<<"Connector::start"<<endl;
  connect_ = true;
  loop_->runInLoop(std::bind(&Connector::startInLoop, this)); // FIXME: unsafe
}

void Connector::startInLoop()
{
  loop_->assertInLoopThread();
  assert(state_ == kDisconnected);
  if (connect_)
  {
  //  cout << "Connector::startInLoop begin connect" << endl;

    connect();
  }
  else
  {
   // LOG_DEBUG << "do not connect";
  }
}

void Connector::stop()
{
  connect_ = false;
  loop_->queueInLoop(std::bind(&Connector::stopInLoop, this)); // FIXME: unsafe
  // FIXME: cancel timer
}

void Connector::stopInLoop()
{
  loop_->assertInLoopThread();
  if (state_ == kConnecting)
  {
    setState(kDisconnected);
    int sockfd = removeAndResetChannel();
    retry(sockfd);
  }
}

void Connector::connect()
{
     char* ip = "127.0.0.1";
    int port_number = 2002;
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;           /* ipv4 */
    server_addr.sin_port = htons(port_number);
    int s = inet_pton(PF_INET, ip, &server_addr.sin_addr);
    if(s <=0)
    {
        //err_exit("inet_pton");
	//cout<<"inet_pton fail"<<s<<endl;
        return ;
    }


    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        //err_exit("socket");
	//cout<<"socket fail"<<endl;
        return ;
    }

    if(::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0){
       
      //  cout<<"CCCCCCCCCCCCCCCCCCCCCCCCCC"<<endl;
        connecting(sockfd);
       // cout<<"20200221----client::connect__set"<<endl;
    }
    else
    {

       //cout<<"20200209----socket::connect fail----20200209"<<endl;
       return;
    }
    
  /*
  int sockfd = sockets::createNonblockingOrDie(serverAddr_.family());
  int ret = sockets::connect(sockfd, serverAddr_.getSockAddr());
  int savedErrno = (ret == 0) ? 0 : errno;
  switch (savedErrno)
  {
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
      connecting(sockfd);
      break;

    case EAGAIN:
    case EADDRINUSE:
    case EADDRNOTAVAIL:
    case ECONNREFUSED:
    case ENETUNREACH:
      retry(sockfd);
      break;

    case EACCES:
    case EPERM:
    case EAFNOSUPPORT:
    case EALREADY:
    case EBADF:
    case EFAULT:
    case ENOTSOCK:
      LOG_SYSERR << "connect error in Connector::startInLoop " << savedErrno;
      sockets::close(sockfd);
      break;

    default:
      LOG_SYSERR << "Unexpected error in Connector::startInLoop " << savedErrno;
      sockets::close(sockfd);
      // connectErrorCallback_();
      break;
  }
*/
}

void Connector::restart()
{
/*
  loop_->assertInLoopThread();
  setState(kDisconnected);
  retryDelayMs_ = kInitRetryDelayMs;
  connect_ = true;
  startInLoop();
*/
}

void Connector::connecting(int sockfd)
{

  setState(kConnecting);

//cout<< "WWW"<<endl;
  assert(!channel_);
  channel_.reset(new Channel(loop_, sockfd));

  //cout   << "WWW::::Connector::connecting::new_Channel::" <<  channel_.get() << endl;

  channel_->setWriteCallback(
      std::bind(&Connector::handleWrite, this)); // FIXME: unsafe
  channel_->setErrorCallback(
     std::bind(&Connector::handleError, this)); // FIXME: unsafe

  // channel_->tie(shared_from_this()); is not working,
  // as channel_ is not managed by shared_ptr
  channel_->enableWriting();
   //cout<<"20200210---channel::set----20200209"<<endl;

}

int Connector::removeAndResetChannel()
{

  channel_->disableAll();
  channel_->remove();
  int sockfd = channel_->fd();
  // Can't reset channel_ here, because we are inside Channel::handleEvent
  loop_->queueInLoop(std::bind(&Connector::resetChannel, this)); // FIXME: unsafe
  return sockfd;

}

void Connector::resetChannel()
{
  channel_.reset();
}

void Connector::handleWrite()
{
 //cout  << "---20200209---Connector::handleWrite " << state_ << endl;

  if (state_ == kConnecting)
  {
//   cout << "Connector::handleWrite:::plus++++" <<endl;
    int sockfd = removeAndResetChannel();
     int optval;
    socklen_t optlen = static_cast<socklen_t>(sizeof optval);
    //int err = sockets::getSocketError(sockfd);
  //  if(::getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&optval,&optlen)<0)
    int err = ::getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&optval,&optlen);

  // cout << "---20200220---- kConnecting" << err <<endl;

      if(err <0)
   // if (err)
    {
   //   LOG_WARN << "Connector::handleWrite - SO_ERROR = "
     //          << err << " " << strerror_tl(err);
      retry(sockfd);
    }
       
    else if (isSelfConnect(sockfd))
  // else if (sockets::isSelfConnect(sockfd))
    {
	//cout<<"---20200220--- isSelfConnect"<<endl;
     // LOG_WARN << "Connector::handleWrite - Self connect";
      retry(sockfd);
   }
    else
    {
      
	//cout<<"---20200220--- kConnected"<<endl;
      setState(kConnected);
      if (connect_)
      {
       //cout<<"2020---------kConnected----Connector::newConnectiinCallback---0000"<<endl;
        cout << "one Connect Success" << endl;
	newConnectionCallback_(sockfd);
      }
      else
      {
        ::close(sockfd);
      }
    }
  }
  else
  {
    // what happened?
    assert(state_ == kDisconnected);
  }

}

void Connector::handleError()
{
  //cout<<"Connector::handleError"<<endl;
  exit(0);
/*
 // LOG_ERROR << "Connector::handleError state=" << state_;
  if (state_ == kConnecting)
  {
    int sockfd = removeAndResetChannel();
    int err = sockets::getSocketError(sockfd);
   // LOG_TRACE << "SO_ERROR = " << err << " " << strerror_tl(err);
    retry(sockfd);
  }
*/
}

void Connector::retry(int sockfd)
{
/*
  sockets::close(sockfd);
  setState(kDisconnected);
  if (connect_)
  {
   // LOG_INFO << "Connector::retry - Retry connecting to " << serverAddr_.toIpPort()
     //        << " in " << retryDelayMs_ << " milliseconds. ";
    loop_->runAfter(retryDelayMs_/1000.0,
                    std::bind(&Connector::startInLoop, shared_from_this()));
    retryDelayMs_ = std::min(retryDelayMs_ * 2, kMaxRetryDelayMs);
  }
  else
  {
   // LOG_DEBUG << "do not connect";
  }
*/
}


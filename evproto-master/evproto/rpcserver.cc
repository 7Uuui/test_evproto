#include "rpcserver.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <functional>


//#include "evproto/rpcserver.h"
#include "evproto/rpccontroller.h"
//#include "evproto/httpserver.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>
#include <event2/rpc.h>

#include "Acceptor.h"
#include "eventloop.h"
#include "Callbacks.h"

#include "eventloop.h"
#include "EventLoopThreadPool.h"


using namespace std;
using namespace std::placeholders;


#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000




namespace evproto
{


class EventLoop;
class EventLoopThreadPool;
/*
void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}
*/
RpcServer::RpcServer(EventLoop* loop,int port)
:loop_(loop),
acceptor_(new Acceptor(loop)),
threadPool_(new EventLoopThreadPool(loop)),
connectionCallback_(defaultConnectionCallback),
nextConnId_(1)
{   
    if(NULL == loop_){cout<<"FATAL::eventloop::null"<<endl;}
    if(NULL == acceptor_) {cout<<"FATAL::acceptor::null"<<endl;}
 //  acceptor_->setNewConnectionCallback(std::bind(&RpcServer::newConnection,this));
    acceptor_->setNewConnectionCallback(std::bind(&RpcServer::newConnection,this,_1,_2));
}

RpcServer::~RpcServer()
{
	
		
}
void RpcServer::newConnection(int sockfd,const struct sockaddr_in& peerAddr)
{
//  cout<<"--------S.N.S.N.S.N.S.N--------------"<<endl;
  loop_->assertInLoopThread();
  EventLoop* ioLoop = threadPool_->getNextLoop();
  char buf[64];
  snprintf(buf, sizeof buf, "#%d",  nextConnId_);
  ++nextConnId_;
  string name_ = "name";
  string connName = name_ + buf;
/*
  cout << "TcpServer::newConnection [" << name_
           << "] - new connection [" << connName
           << "] from " << peerAddr.sin_port<<endl;
 // sockaddr_in localAddr(sockets::getLocalAddr(sockfd));
  */ 

   struct sockaddr_in localaddr;
   //memZero(&localaddr,sizeof localaddr);
    memset(&localaddr,0,sizeof(localaddr));
   socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
  ::getsockname(sockfd,(struct sockaddr *)&localaddr,&addrlen);

  // FIXME poll with zero timeout to double confirm the new connection
  // FIXME use make_shared if necessary

  
 // cout<<"---TcpConnectionPtr--"<<endl;


  TcpConnectionPtr conn(new TcpConnection(ioLoop,
                                          connName,
                                          sockfd,
                                          localaddr,
                                          peerAddr));
  connections_[connName] = conn;
  conn->setConnectionCallback(connectionCallback_);
  conn->setMessageCallback(messageCallback_);
  conn->setWriteCompleteCallback(writeCompleteCallback_);
  conn->setCloseCallback(
      std::bind(&RpcServer::removeConnection, this, _1)); // FIXME: unsafe

 // cout<<"+++TcpConnectionPtr+++"<<conn<<endl;

  ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
   //cout<<"rpcServer::newConnection"<<endl;

}
/*
void RpcServer::setThreadNum(int num)
{
  threadPool_->setThreadNum(2);

}
*/

void RpcServer::start()
{
 
  threadPool_->start(threadInitCallback_);
  assert(!acceptor_->listenning());  
  
 // cout<<"rpcServer::start"<<endl;
  
  loop_->runInLoop(std::bind(&Acceptor::listen , get_pointer(acceptor_)));

}


bool RpcServer::registerService(gpb::Service* service)
{
	// cout << "[[[RpcServer]]] : registerService" << endl;
	 //std::map<std::string,Service*> services;
	 const google::protobuf::ServiceDescriptor* desc = service->GetDescriptor();
     services_[desc->full_name()] = service;
	
}

//bool RpcServer::registerService(){}
void RpcServer::removeConnection(const TcpConnectionPtr& conn)
{
loop_->runInLoop(std::bind(&RpcServer::removeConnectionInLoop,this,conn));
}
void RpcServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
loop_->assertInLoopThread();
size_t n = connections_.erase(conn->name());
(void)n;
assert(n=1);
EventLoop* ioLoop = conn->getLoop();
ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed,conn));
}


}

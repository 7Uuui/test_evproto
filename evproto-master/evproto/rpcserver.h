#ifndef EVPROTO_H
#define EVPROTO_H

#include "evproto/common.h"
#include "evproto/eventloop.h"
#include "evproto/TcpConnection.h"
#include <map>
#include <google/protobuf/service.h>
#include <netinet/in.h>


using namespace std;

namespace evproto
{

class Acceptor;
class EventLoop;
class EventLoopThreadPool;

class RpcServer
{
public:

typedef std::function<void(EventLoop*)> ThreadInitCallback;

RpcServer(EventLoop* loop,int port);
~RpcServer();
bool registerService(gpb::Service* service);
bool registerService();
void newConnection(int sockfd,const struct sockaddr_in& peerAddr);
void start();

void setMessageCallback(const MessageCallback& cb){messageCallback_ = cb;}

void setWriteCompleteCallback(const WriteCompleteCallback& cb){writeCompleteCallback_ = cb;}





private:


//void newConnection(int sockfd,const InetAddress& peerAddr);
void removeConnection(const TcpConnectionPtr& conn);

void removeConnectionInLoop(const TcpConnectionPtr& conn);



std::shared_ptr<EventLoopThreadPool> threadPool_;

std::map<std::string,gpb::Service*> services_;
std::unique_ptr<Acceptor> acceptor_;
EventLoop* loop_;
int nextConnId_;
ThreadInitCallback threadInitCallback_;



ConnectionCallback connectionCallback_;
MessageCallback messageCallback_;
WriteCompleteCallback writeCompleteCallback_;


typedef std::map<string,TcpConnectionPtr> ConnectionMap;
ConnectionMap connections_;



};

}
#endif

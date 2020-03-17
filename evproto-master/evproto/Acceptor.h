#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <functional>
#include <stdio.h>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "eventloop.h"
#include "Channel.h"


using namespace std;

namespace evproto
{

//struct sockaddr_in;

class Acceptor
{

public:
//typedef std::function<void (int sockfd)> NewConnectionCallback; 

 typedef std::function<void  (int sockfd,const struct sockaddr_in&)> NewConnectionCallback; 


Acceptor(EventLoop* loop);
~Acceptor();

void setNewConnectionCallback(const NewConnectionCallback& cb)
{ newConnectionCallback_ = cb;}

NewConnectionCallback newConnectionCallback_;


bool listenning() const {return listenning_;}

void listen();
void handleRead();

private:
EventLoop* loop_;
int acceptSocket_;
Channel acceptChannel_;
bool listenning_;
};
}
#endif

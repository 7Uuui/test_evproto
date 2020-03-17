// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpcchannel.h"
#include "evproto/rpccontroller.h"
#include "evproto/eventloop.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/rpc.h>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>


using namespace std;

namespace evproto
{

RpcChannel::RpcChannel(EventLoop* loop)
  : loop_(loop)
 // : loop_(loop),
 //   pool_(CHECK_NOTNULL(::evrpc_pool_new(loop->eventBase())))
{
cout<<"[[[RpcChannel]]]::RpcChannel"<<endl;
}

RpcChannel::~RpcChannel()
{
/*
  for (size_t i = 0; i < addedConns_.size(); ++i)
  {
    ::evrpc_pool_remove_connection(pool_, addedConns_[i]);
    ::evhttp_connection_free(addedConns_[i]);
  }

  ::evrpc_pool_free(pool_);
*/
}
/*
bool RpcChannel::addServer(const char* host, uint16_t port)
{
  struct evhttp_connection* evcon = ::evhttp_connection_base_new(
      NULL, NULL, host, port);
  if (evcon)
  {
    ::evrpc_pool_add_connection(pool_, evcon);
    addedConns_.push_back(evcon);
  }
  return evcon != NULL;
}

void RpcChannel::CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done)
{
  cout << "[[[RpcChannel]]]::CallMethod" << method->name() << endl;
  cout << "[[[RpcChannel]]]::CallMethod" << method->full_name() << endl;
  ::evrpc_send_request_generic(
      pool_,
      const_cast<gpb::Message*>(request),
      response,
      &RpcController::statusCallback,
      done,
      method->full_name().c_str(),
      &RpcController::marshal,

      &RpcController::unmarshal);
}
*/

int create_socket(const char *ip, const int port_number)
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;           /* ipv4 */
    server_addr.sin_port = htons(port_number);
    int s = inet_pton(PF_INET, ip, &server_addr.sin_addr);
    if(s <=0)
    {
        //err_exit("inet_pton");
	cout<<"inet_pton fail"<<s<<endl;
        return -1;
    }


    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        //err_exit("socket");
	cout<<"socket fail"<<endl;
        return -1;
    }

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        //err_exit("connect");
	cout<<"connect_20200101 fail"<<endl;
         return -1;
    }
    
   cout<<"RpcChannel::create_socket success"<<endl;
   cout<<"RpcChannel::connected  success"<<endl;
    return sockfd;
}
//connect with server
bool RpcChannel::addServer(const char* ip,uint16_t port)
{
cout<<"RpcChannel::addServer"<<endl;
sock = create_socket(ip, port);
return true;
}
//sendmsg
//control([msg_queue])
void RpcChannel::CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done)
{
 /*
  RpcMessage message;
  message.set_type(REQUEST);
  int64_t id = id_.incrementAndGet();
  message.set_id(id);
  message.set_service(method->service()->full_name());
  message.set_method(method->name());
  message.set_request(request->SerializeAsString()); // FIXME: error check

  OutstandingCall out = { response, done };
  {
  MutexLockGuard lock(mutex_);
  outstandings_[id] = out;
  }
  */
  //codec_.send(conn_, message);
// write(sock, message.c_str(), message.size());
ssize_t n = ::write(sock,"123",3);
if(n != -1)
{
cout<<"rpcchannel::CallMethod success"<<endl;
}
else
{
cout<<"rpcchannel::CallMethod fail"<<endl;
}
}
}


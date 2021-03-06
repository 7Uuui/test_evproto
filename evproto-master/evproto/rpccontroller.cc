// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpccontroller.h"

#include <glog/logging.h>
#include <google/protobuf/message.h>

#include <sys/queue.h>
#include <event2/buffer.h>
//#include <event2/event.h>
//#include <event2/rpc.h>
#include <event2/rpc_struct.h>

#include <iostream>
using namespace std;

namespace evproto
{

RpcController::RpcController()
{
cout << "RpcController ||| RpcController" << endl;
}

RpcController::~RpcController()
{
}

void RpcController::statusCallback(
      struct evrpc_status *status,
      void* request,
      void* response,
      void *arg)
{
 // VLOG(0) 
  cout << "rpcController ||| [statusCallback] " << status->error << endl;
  gpb::Closure* closure = static_cast<gpb::Closure*>(arg);
  closure->Run();
}

void RpcController::marshal(struct evbuffer* buf, void* arg)
{
  const gpb::Message* msg = static_cast<const gpb::Message*>(arg);
  cout << "rpcController ||| [marshal]" << msg->GetTypeName() << endl;
  std::string s = msg->SerializeAsString();
  evbuffer_add(buf, s.data(), s.size());
}

int RpcController::unmarshal(void* arg, struct evbuffer* buf)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  cout << "rpcController ||| [unmarshal]" << msg->GetTypeName() << endl;
  size_t len = evbuffer_get_length(buf);
  std::vector<char> array(len);
  size_t nread = evbuffer_remove(buf, &*array.begin(), len);
  CHECK_EQ(len, nread);
  bool ok = msg->ParseFromArray(&*array.begin(), nread);
  return ok ? 0 : -1;
}

void RpcController::clear(void* arg)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  cout << "rpcController ||| [clear]" << msg->GetTypeName() << endl;
}

void* RpcController::newMessage(void* arg)
{
  const gpb::Message* msg = static_cast<const gpb::Message*>(arg);
  cout << "rpcController ||| [newMessage]" << msg->GetTypeName() << endl;
  return msg->New();
}

void RpcController::deleteMessage(void* arg)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  cout << "rpcController ||| [deleteMessage]" << msg->GetTypeName() << endl;
  delete msg;
}

int RpcController::complete(void* arg)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  cout << "rpcController ||| complete " << msg->GetTypeName() << endl;
  return 0;
}

}

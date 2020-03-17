// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/eventloop.h"

#include <glog/logging.h>

#include <event2/event.h>

#include <iostream>
using namespace std;

namespace evproto
{

EventLoop::EventLoop()
  : base_(CHECK_NOTNULL(::event_base_new()))
{
 //LOG(INFO)
  cout << "Using Libevent with backend method "
            << ::event_base_get_method(base_) << endl;
}

EventLoop::~EventLoop()
{
  ::event_base_free(base_);
}

int EventLoop::loop()
{
  return ::event_base_loop(base_, 0);
}

struct event_base* EventLoop::eventBase()
{
  return base_;
}

}

// iCopyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_EVENTLOOP_H
#define EVPROTO_EVENTLOOP_H

#include "evproto/common.h"
#include "Timestamp.h"


#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>



#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>


#include "CurrentThread.h"
#include "Mutex.h"


using namespace std;

struct epoll_event;

namespace evproto
{

class EPollPoller;
class Poller;
class Channel;



class EventLoop
{
 public:
typedef std::function<void()> Functor;
  EventLoop();
  ~EventLoop();

   void quit();
//  void handleRead(epoll_event* ev);
  void handleRead();
  int loop();
  bool hasChannel(Channel* channel);

  int getThreadId();

 void wakeup();
 void updateChannel(Channel* channel);
 void removeChannel(Channel* channel);


//20200204
  void assertInLoopThread(){
  if(!isInLoopThread()){
      abortNotInLoopThread();
    }

   }   


  Timestamp pollReturnTime() const {return pollReturnTime_;}
  int64_t iteration() const {return iteration_;}


  // pid_t gettid(){return static_cast<pid_t>(::syscall(SYS_gettid);}


//   bool isInLoopThread() const { return threadId_ == syscall(SYS_gettid);}
//  bool isInLoopThread() const{return threadId_ == CurrentThread::tid();}
  
    
    bool isInLoopThread() const;
    
    
    bool eventHandling() const {return eventHandling_;}


  // void setContext(const boost::any& context){context_=context;}
  // const boost::any& getContext() const{return context_;}
   
  // boost::any* getContext(){return &context_;}


//20200204
  void runInLoop(Functor cb);
void queueInLoop(Functor cb);
//  struct event_base* eventBase();
   static EventLoop* getEventLoopOfCurrentThread(); 
private:
//  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(EventLoop);
 // struct event_base* const base_;
 

  void abortNotInLoopThread();

  int listenfd; //socket 
  int epfd; //epoll


   typedef std::vector<struct epoll_event> EventList;
   EventList events_;


   typedef std::vector<Channel*> ChannelList;
   ChannelList activeChannels_;

   Channel* currentActiveChannel_;
   


    std::unique_ptr<Poller> poller_;
  // std::unique_ptr<EPollPoller> poller_;
   std::unique_ptr<Channel> wakeupChannel_;

   mutable MutexLock mutex_;
   std::vector<Functor> pendingFunctors_ ;// GUARDED_BY(mutex_);

    void doPendingFunctors();

    bool looping_;
    std::atomic<bool> quit_;
//  bool quit_;  
    bool eventHandling_;
    bool callingPendingFunctors_;
   int wakeupFd_;
   Timestamp pollReturnTime_;
  // boost::any context_;
   //private-------------------------------------
   const pid_t threadId_;
   int64_t iteration_;
};

}

#endif  // EVPROTO_EVENTLOOP_H

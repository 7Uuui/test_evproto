#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H

#include <functional>
#include <string>
#include <vector>
#include <memory>
#include "Thread.h"
#include "Mutex.h"
#include "Condition.h"


using namespace std;
namespace evproto
{
class EventLoop;
class EventLoopThread
{
public:
   typedef std::function<void(EventLoop*)> ThreadInitCallback;
   EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),const string& name = string());
  ~EventLoopThread();
  EventLoop* startLoop();

private:
   void threadFunc();
   
   Thread thread_;
   MutexLock mutex_;  
   Condition cond_;
   EventLoop* loop_;
   ThreadInitCallback callback_;
   bool exiting_;
};
}

#endif

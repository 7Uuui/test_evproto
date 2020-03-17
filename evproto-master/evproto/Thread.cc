// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "Thread.h"
#include "CurrentThread.h"
//#include "Exception.h"
//#include "Logging.h"

#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>


#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/weak_ptr.hpp>

namespace evproto
{
namespace CurrentThread
{
	__thread int t_cachedTid = 0;
	
	__thread char t_tidString[32];
	
	__thread int t_tidStringLength = 6;
	
	__thread const char* t_threadName = "unknown";
	
	const bool sameType = boost::is_same<int,pid_t>::value;
	BOOST_STATIC_ASSERT(sameType);

}



namespace detail
{

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
  evproto::CurrentThread::t_cachedTid = 0;
  evproto::CurrentThread::t_threadName = "main";
  CurrentThread::tid();
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer
{
 public:
  ThreadNameInitializer()
  {
    evproto::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);
  }
};

ThreadNameInitializer init;

struct ThreadData
{
  typedef evproto::Thread::ThreadFunc ThreadFunc;
  ThreadFunc func_;
  string name_;
 pid_t* tid_;//01
//CountDownLatch* latch_;//01
  boost::weak_ptr<pid_t> wkTid_;
  



  ThreadData(const ThreadFunc& func,
		const string& name,
		const boost::shared_ptr<pid_t>& tid)
	:func_(func),
	name_(name),
	wkTid_(tid){}

  void runInThread()
  {
   //*tid_ = evproto::CurrentThread::tid();//01
    
   pid_t tid = evproto::CurrentThread::tid();//02
    boost::shared_ptr<pid_t> ptid = wkTid_.lock();

    if(ptid)
    {
	*ptid = tid;
	ptid.reset();
    }
    
   // tid_ = NULL;//01
    

    evproto::CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();
    ::prctl(PR_SET_NAME, evproto::CurrentThread::t_threadName);
    try
    {
      func_();
      evproto::CurrentThread::t_threadName = "finished";
    }
    catch (const std::exception& ex)
    {
      evproto::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
    //  fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
      abort();
    }
    catch (const std::exception& ex)
    {
      evproto::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    }
    catch (...)
    {
      evproto::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
      throw; // rethrow
    }
  }
};

void* startThread(void* obj)
{
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->runInThread();
  delete data;
  return NULL;
}

}  // namespace detail

void CurrentThread::cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = detail::gettid();
    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}

void CurrentThread::sleepUsec(int64_t usec)
{
  struct timespec ts = { 0, 0 };
//  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  //ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  //::nanosleep(&ts, NULL);
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(ThreadFunc func, const string& n)
  : started_(false),
    joined_(false),
    pthreadId_(0),
    //tid_(0),//01
    tid_(new pid_t(0)),//02
    func_(std::move(func)),
    name_(n)
{
  setDefaultName();
}

Thread::~Thread()
{
  if (started_ && !joined_)
  {
    pthread_detach(pthreadId_);
  }
}

void Thread::setDefaultName()
{
  int num = numCreated_.incrementAndGet();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::start()
{
  assert(!started_);
  started_ = true;
  // FIXME: move(func_)
  //detail::ThreadData* data = new detail::ThreadData(func_, name_, &tid_);//01
  detail::ThreadData* data = new detail::ThreadData(func_, name_, tid_);//02
  if (pthread_create(&pthreadId_, NULL, &detail::startThread, data))
  {
    started_ = false;
    delete data; // or no delete?
//    LOG_SYSFATAL << "Failed in pthread_create";
  }
//  else
 // {
 //   latch_.wait();
  //  assert(tid_ > 0);
 // }
}

int Thread::join()
{
  assert(started_);
  assert(!joined_);
  joined_ = true;
  return pthread_join(pthreadId_, NULL);
}

}  // namespace muduo

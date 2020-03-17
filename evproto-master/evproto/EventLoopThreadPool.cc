#include "EventLoopThreadPool.h"

#include "eventloop.h"
#include "EventLoopThread.h"

namespace evproto
{

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop)
:baseLoop_(baseLoop),
name_("name"),
started_(false),
next_(0)
{}
EventLoopThreadPool::~EventLoopThreadPool(){}

EventLoop* EventLoopThreadPool::getNextLoop()
{

baseLoop_->assertInLoopThread();
assert(started_);
EventLoop* loop=baseLoop_;
if(!loops_.empty())
{
    loop = loops_[next_];
    ++next_;
    if(next_ >= loops_.size())
    {next_ = 0;}
}  
return loop;
}


void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
assert(!started_);
baseLoop_->assertInLoopThread();
started_ = true;
for(int i = 0;i<2;++i)
{

   char buf[name_.size() +32];
  snprintf(buf,sizeof buf,"%s%d",name_.c_str(),i);
  EventLoopThread* t = new EventLoopThread(cb,buf);
  threads_.push_back(std::unique_ptr<EventLoopThread>(t));
  loops_.push_back(t->startLoop());
  
  cout<<"\n pool::start \n"<<endl;
}

}
}

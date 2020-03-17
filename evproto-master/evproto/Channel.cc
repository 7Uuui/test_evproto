#include "Channel.h"

#include <linux/kernel.h>


#include <sstream>
namespace evproto
{
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop,int fd__)
:fd_(fd__),
loop_(loop),
index_(-1),
events_(0),
revents_(0),
tied_(false),
eventHandling_(false),
addedToLoop_(false)
{
 cout<<"---2---Channel"<<this<<endl;

}

Channel::~Channel()
{
assert(!eventHandling_);
assert(!addedToLoop_);
 if(loop_->isInLoopThread())
 {
  
  assert(!loop_->hasChannel(this));
 }

//cout<<"ZZZ::channel::XIGOU::"<<this<<endl;

}

void Channel::tie(const std::shared_ptr<void>& obj)
{
 tie_ = obj;
 tied_ = true;

}

int Channel::fd() const 
{
	//cout<<"ZZZ::channel::Getfd::"<<fd_<<endl;
	return fd_;
}

void Channel::enableReading()
{	
	//cout<<"---0--- Channel"<<this<<"enableReading"<<endl;
        events_ |= kReadEvent;
	update();
}

void Channel::enableWriting()
{
	//cout<<"---0--- Channel"<<this<<"enableWrite"<<endl;
        events_ |= kWriteEvent;
	update();
}

void Channel::handleEvent(Timestamp receiveTime)
{
//  cout<<"---C.H.C.H.C.H---"<<this<<"tied_::"<<tied_<<endl;
  std::shared_ptr<void> guard;
  if (tied_)
  {
    guard = tie_.lock();
    if (guard)
    {
      handleEventWithGuard(receiveTime);
    }
  }
  else
  {
    handleEventWithGuard(receiveTime);
  }
}

void Channel::handleEventWithGuard(Timestamp receiveTime)
{
  eventHandling_ = true;
//  cout  << "-----H.A.N.D.L.E.E.V.E.N.T.W.I.T.H.G.U.A.R.D-----"<< reventsToString()<<endl;
  if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
  {
    if (logHup_)
    {
  //    LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLHUP";
    }
    cout<<"closeCallback\n";
    if (closeCallback_) {closeCallback_();}// cout<<"closeCallback success\n";}
    else{}//cout<<"closeCallback_ fail\n";}
  }

  if (revents_ & POLLNVAL)
  {
    //  cout<<"---handleevent---Channel::handle_event() POLLNVAL\n";
   // LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLNVAL";
  }

  if (revents_ & (POLLERR | POLLNVAL))
  {
    if (errorCallback_)
    {
	errorCallback_();
	//cout<<"errorCallback success\n";
    }
    else
    {
          //cout<<"errorCallback fail\n";
    }
  }
  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
  {
    if (readCallback_)
    {
	//cout << "channel::" << this << "readCallback success::" << &readCallback_ << "\n";
 //        cout << "channel::" << this << "read_C.A.L.L.B.A.C.K" << endl; 
	 readCallback_(receiveTime);
    }
    else
    {
//	errorCallback_();
//	cout<<"readCallback fail\n";
    }
  }
  if (revents_ & POLLOUT)
  {
    if (writeCallback_)
    {
	 cout << "channel::" << this << "write_C.A.L.L.B.A.C.K" << endl;
	 writeCallback_();
	 //cout<<"channel::"<<this<<"writeCallbacl success::"<<&writeCallback_ << "\n";
    }
    else
    {
//	errorCallback_();
//	cout<<"writeCallback fail\n";
    }
  }
  eventHandling_ = false;
}
void Channel::setReadCallback(ReadEventCallback cb)
{
   readCallback_ = std::move(cb);
   if(readCallback_)
   {
           //printk("%pf,%pF\n",readCallback_,readCallback_);
          // printf("%p\n",(void*)readCallback_);
	 //    printf("%p\n",&readCallback_);          
          //  cout<<"Channel::"<<this<<"ReadCallback::"<<&readCallback_<<endl;
   	  //  cout<<"=========20200203WHERE ReadCallback========="<<endl;
   }
   
}
void Channel::setErrorCallback(EventCallback cb)
{
 errorCallback_ = std::move(cb);
 
}

void Channel::setWriteCallback(EventCallback cb)
{
  // cout<<"Channel::"<<this<<"setWriteCallback::"<<&cb<<endl;
//   cout<<"Channel::setWriteCallback"<<*cb<<endl;
   writeCallback_ = std::move(cb);
}
//void Channel::handleEvent(Timestamp receiveTime)
//{
/*
///cout<<"Channel::handleEvent"<<endl;
//   cout << "---20200209---Channel::handleEvent:::" << revents_ << endl;
//   cout << "POLLHUP" << POLLHUP << endl;
//   cout << "POLLIN" << POLLIN << endl;
//   cout << POLLNVAL << endl;
//   cout << (POLLERR|POLLNVAL) << endl;
//   cout << (POLLIN|POLLPRI|POLLRDHUP) << endl;
//   cout << POLLOUT << endl;
//   cout << "EPOLLIN" << EPOLLIN << endl;
//   cout << EPOLLOUT << endl;
//   cout << "EPOLLIN|EPOLLET" << (EPOLLIN|EPOLLET) << endl;
   if(revents_ & (POLLIN | POLLPRI | POLLRDHUP))
   {
       if(readCallback_){ readCallback_(receiveTime);}
   }
   if(revents_ & POLLOUT)
   {
        if(writeCallback_) {writeCallback_();}
   }
  // if(revents_ & EPOLLIN || revents_ & 0)
    if(revents_ == 0)
   {
     //   cout<<"loop++fd"<<fd_;
       if(readCallback_)
       {
           readCallback_(receiveTime);

         //  cout<<"EPOLLIN::readCallback_success"<<endl;
       }
       else
       {
	   errorCallback_();
          // cout<<"EPOLLIN::readCallback_fail"<<endl;
       }
   }
*/   
//}


//KINGKINGKING
void Channel::update()
{
//cout<<"ZZZZZ::Channel::update::"<<this<<endl;
addedToLoop_ = true;
loop_->updateChannel(this);

}
void Channel::remove()
{
  assert(isNoneEvent());
  addedToLoop_ = false;
  loop_->removeChannel(this);
}


string Channel::reventsToString() const
{
  return eventsToString(fd_, revents_);
}

string Channel::eventsToString() const
{
  return eventsToString(fd_, events_);
}

string Channel::eventsToString(int fd, int ev)
{
  std::ostringstream oss;
  oss << fd << ": ";
  if (ev & POLLIN)
    oss << "IN ";
  if (ev & POLLPRI)
    oss << "PRI ";
  if (ev & POLLOUT)
    oss << "OUT ";
  if (ev & POLLHUP)
    oss << "HUP ";
  if (ev & POLLRDHUP)
    oss << "RDHUP ";
  if (ev & POLLERR)
    oss << "ERR ";
  if (ev & POLLNVAL)
    oss << "NVAL ";

  return oss.str();
}






}

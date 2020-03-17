//

#include "eventloop.h"
#include "EpollPoller.h"
#include "Poller.h"
#include "Mutex.h"
#include "Channel.h"
#include <glog/logging.h>

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

namespace evproto
{
__thread EventLoop* t_loopInThisThread = 0;

const int kPollTimeMs = 10000;


int createEventfd()
{
  int evfd = ::eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
  if(evfd < 0){}
  return evfd;
}


EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
 return t_loopInThisThread;
}


EventLoop::EventLoop()
:wakeupFd_(createEventfd()),
quit_(false),
looping_(false),
eventHandling_(false),
callingPendingFunctors_(false),
iteration_(0),
threadId_(CurrentThread::tid()),
//threadId_(syscall(SYS_gettid)),
wakeupChannel_(new Channel(this,wakeupFd_)),
//poller_(new EPollPoller(this))
poller_(new EPollPoller(this))
 {
   cout<<"---1---EventLoop create"<<this<<"in thread"<<threadId_<<endl;
  if(t_loopInThisThread)
  {
    cout<<"---1---another eventloop::"<<t_loopInThisThread<<"exists in this thread"<<threadId_<<endl;
  }
  else
  {
    cout<<"---1---eventloop::"<<this << endl;
    t_loopInThisThread = this;
   }

   

  wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead,this));
  wakeupChannel_->enableReading();

}

EventLoop::~EventLoop()
//  ::event_base_free(base_);
{
  wakeupChannel_->disableAll();
  wakeupChannel_->remove();
  ::close(wakeupFd_);
  t_loopInThisThread = NULL;

}

int  EventLoop::getThreadId()
{
	return threadId_;
}

void EventLoop::quit()
{
 quit_ = true;
 if(!isInLoopThread()){wakeup();}

}

void EventLoop::handleRead()
{
char line[MAXLINE];
int n = ::read(wakeupFd_,line,MAXLINE);

}
bool EventLoop::isInLoopThread() const
{
//	cout<<"+++eventloop::isInLoopThread::+++"<<"threadId_::"<<threadId_<<"CurrentThread::tid()::"<<CurrentThread::tid()<<endl;
	 return threadId_ == CurrentThread::tid();

}

//KINGKINGKINGKINGKING
void EventLoop::updateChannel(Channel* channel)
{ 
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    
  //  cout<<"ZZZZZ::EventLoop::updateChannel::"<<channel<<endl;
    poller_->updateChannel(channel);
}
void EventLoop::removeChannel(Channel* channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    if(eventHandling_)
    {
	assert(currentActiveChannel_ == channel || std::find(activeChannels_.begin(),activeChannels_.end(), channel ) == activeChannels_.end());
    }
    poller_->removeChannel(channel);

}
 
void EventLoop::runInLoop(Functor cb)
{
  //if(true)
   if(isInLoopThread())
  {
     //cout<<"EventLoop::runInLoop::isInLoopThread::begin"<<endl;
     cb();
     //cout<<"EventLoop::runInLoop::isInLoopThread::end"<<endl;
  }
  else
  {
    
     //cout<<"EventLoop::notrunInLoop::isInLoopThread::begin"<<endl;
    queueInLoop(std::move(cb));
    
    // cout<<"EventLoop::notrunInLoop::isInLoopThread::end"<<endl;
  }

}

bool EventLoop::hasChannel(Channel* channel)
{
 assert(channel->ownerLoop() == this);
 assertInLoopThread();
 return poller_->hasChannel(channel);

}


void EventLoop::queueInLoop(Functor cb)
{
 {
//   cout<<"A.A.A.A.A.A.A."<<endl;
   MutexLockGuard lock(mutex_);
//   cout<<"B.B.B.B.B.B.B."<<endl;
   pendingFunctors_.push_back(std::move(cb));
 //  cout<<"C.C.C.C.C.C.C."<<endl;
 }
 if(!isInLoopThread() || callingPendingFunctors_)
 {
    cout<<".w.a.k.e.u.p."<<endl;
    wakeup();
 }

}












int EventLoop::loop()
{
  assert(!looping_);
  
 // cout<<"!looping_"<<endl;; 
 
  assertInLoopThread();
 // cout<<"assertInLoopThread"<<endl;
  looping_ = true;
  quit_ = false;
  

  
  while(!quit_)
  {
//    cout<<"---9---::"<<threadId_<<endl;

     activeChannels_.clear();
    pollReturnTime_ = poller_->poll(kPollTimeMs,&activeChannels_);
     if(activeChannels_.size() > 0)
     {
	//cout<<"---L.O.O.P.L.O.O.P---"<<activeChannels_.size()<<endl;
     }

     ++iteration_;
      eventHandling_ = true;
     for(Channel* channel : activeChannels_)
     {
          currentActiveChannel_ = channel;
          currentActiveChannel_->handleEvent(pollReturnTime_);
        // cout<<"---3--- channel::CLIENT"<<currentActiveChannel_<<"threadId::"<<threadId_<<endl;
     }
     currentActiveChannel_ = NULL;
     eventHandling_ = false;
     doPendingFunctors();


  }
/*  
    int  connfd , sockfd;
    struct sockaddr_in clientaddr;
    socklen_t clilen;
    struct epoll_event ev , events[20];  
    char line[MAXLINE];
    int i;
    int maxi = 0;
    ssize_t n;
    int nfds;
    for ( ; ; ) {
        activeChannels_.clear();
       nfds=epoll_wait(epfd,events,20,500);
//	nfds=epoll_wait(epfd,&*events_.begin(),static_cast<int>(events_.size()),500);
      
        for(i=0;i<nfds;++i)
        {
	   // cout<<"eventloop::LOOP1LOOP1"<<nfds<<endl;
           // cout<<"eventloop::LOOP2LOOP2"<<events_.size()<<endl;
            if(events[i].data.fd==listenfd)
            {
                connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
                if(connfd<0){
                   // perror("connfd<0");
                    exit(1);
                }
                char *str = inet_ntoa(clientaddr.sin_addr);
               // cout << "accapt a connection from " << str << endl;
                ev.data.fd=connfd;
                ev.events=EPOLLIN|EPOLLET;
               // cout << "new connected" << endl;

                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN)
	    {
               // cout << "EPOLLIN" << endl;
                if ( (sockfd = events[i].data.fd) < 0)
                    continue;
                if ( (n = read(sockfd, line, MAXLINE)) < 0) {
                    if (errno == ECONNRESET) {
                        close(sockfd);
                        events[i].data.fd = -1;
                    } else
                        std::cout<<"readline error"<<std::endl;
                } else if (n == 0) {
                    close(sockfd);
                    events[i].data.fd = -1;
                }
                line[n] = '/0';
              //  cout << "read " << line << endl;
                ev.data.fd=sockfd;
                ev.events=EPOLLOUT|EPOLLET;
             }
            else if(events[i].events&EPOLLOUT) 
            {
                sockfd = events[i].data.fd;
                write(sockfd, line, n);
                ev.data.fd=sockfd;
                ev.events=EPOLLIN|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);

                //cout << "OUT" << endl;
            }
        }
      
 }
*/
  //return ::event_base_loop(base_, 0);
}



void EventLoop::doPendingFunctors()
{
  std::vector<Functor> functors;
  callingPendingFunctors_ = true;


  {
    MutexLockGuard lock(mutex_);
    functors.swap(pendingFunctors_);
  }


  for(const Functor& functor : functors)
  {functor();}

   callingPendingFunctors_ = false;

}

void EventLoop::abortNotInLoopThread()
{
cout<<"---A.B.O.R.T.A.B.O.R.T---abortNotInLoopThread"<<this<<"threadid::"<<threadId_<<"current threadid"<<CurrentThread::tid()<<endl;

}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	ssize_t n = ::write(wakeupFd_,&one,sizeof one);
	if(n != sizeof one)
	{
	 //   cout<<"wakeup error"<<endl;
	}


}


}

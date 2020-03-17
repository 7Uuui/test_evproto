#ifndef EPOLL_H
#define EPOLL_H

#include <iostream>
#include <map>
#include <vector>
#include "eventloop.h"
#include <sys/epoll.h>
#include "Poller.h"
//#include "Timestamp.h"
using namespace std;


struct epoll_event;
namespace evproto
{
class Timestamp;
class Channel;

class EPollPoller : public Poller
{
public:
  EPollPoller(EventLoop* loop);
  ~EPollPoller();
/*
  void assertInLoopThread() const
  {
    ownerLoop_->assertInLoopThread();
  }
*/
//  typedef std::vector<Channel*> ChannelList;
  Timestamp poll(int timeoutMs,ChannelList* activeChannels);
  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);
  void fillActiveChannels(int numEvents,ChannelList* activeChannel);
  void update(int operation,Channel* channel); 



  
//protected:
 // typedef std::map<int,Channel*> ChannelMap;
 // ChannelMap channels_;
private:
    
   struct epoll_event events[20];
   static const char* operationToString(int op);
   
//   struct epoll_event event2[20];
   typedef std::vector<struct epoll_event> EventList;
   EventList events_;
   int epollfd_;
   EventLoop* loop_;
//   EventList events_;
};

}
#endif

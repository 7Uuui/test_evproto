#ifndef POLLER_H
#define POLLER_H


#include <map>
#include <vector>

#include "Timestamp.h"
#include "eventloop.h"



namespace evproto
{
class Channel;
class Poller
{
public:
  typedef std::vector<Channel*> ChannelList;
  Poller(EventLoop* loop);
  virtual ~Poller(); 
  virtual Timestamp poll(int timeoutMs,ChannelList* activeChannels) = 0;
  virtual void updateChannel(Channel* channel) = 0;
  virtual void removeChannel(Channel* channel) = 0;
  virtual bool hasChannel(Channel* channel) const;
  void assertInLoopThread() const
  {
    ownerLoop_->assertInLoopThread();
  }
protected:
  typedef std::map<int,Channel*> ChannelMap;
  ChannelMap channels_;
private:
  EventLoop* ownerLoop_;
};

}
#endif

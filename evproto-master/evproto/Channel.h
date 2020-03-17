#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include "eventloop.h"
#include "Timestamp.h"
#include <sys/poll.h>
#include <sys/epoll.h>


namespace evproto
{
//class Timestamp;


class Channel
{
public:
  typedef std::function<void()> EventCallback;
  typedef std::function<void(Timestamp)> ReadEventCallback;
  Channel(EventLoop* loop,int fd);
  ~Channel();


  void tie(const std::shared_ptr<void>&);

  void setReadCallback(ReadEventCallback cb);//{readCallback_ = std::move(cb);}
  void setWriteCallback(EventCallback cb);//{writeCallback_ = std::move(cb);}
 

  void setCloseCallback(EventCallback cb)
  { closeCallback_ = std::move(cb);}

  void setErrorCallback(EventCallback cb);

  void handleEvent(Timestamp receiveTime);   
  void handleEventWithGuard(Timestamp receiveTime);

//  int fd() const {return fd_;}
   int fd() const;



  int events() const {return events_;}
  void set_revents(int revt){revents_ = revt;}  
  int index(){return index_;}
  void set_index(int idx){index_ = idx;}
 

  string reventsToString() const;
  string eventsToString() const;



 bool isNoneEvent() const {return events_ == kNoneEvent;}
  
/*
  void enableReading(){events_ |= kReadEvent;update();}

  void enableWriting() {events_ |= kWriteEvent;update(); }
*/

  void enableReading();//{events_ |= kReadEvent;update();}

  void enableWriting();// {events_ |= kWriteEvent;update(); }

  void disableReading(){events_ &= ~kReadEvent;update();}

  void disableWriting() {events_ &= ~kWriteEvent;update(); }



//  void enableReading(){events_ |= POLLIN | POLLPRI; update();}
   void disableAll() {events_ = kNoneEvent;update();}

   bool isWriting() const {return events_ & kWriteEvent;}

   bool isReading() const {return events_ & kReadEvent;}
  void remove();

   EventLoop* ownerLoop() {return loop_;}



private:
  static string eventsToString(int fd,int ev);

  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;
  void update();
  ReadEventCallback readCallback_;
  EventCallback writeCallback_;
  EventCallback closeCallback_;
  EventCallback errorCallback_;




  const int fd_;
  int events_;
  int revents_;
  int index_;


  EventLoop* loop_;
  std::weak_ptr<void> tie_;
  bool tied_;
  bool addedToLoop_;

  bool eventHandling_;
  bool logHup_;


};
}

#endif

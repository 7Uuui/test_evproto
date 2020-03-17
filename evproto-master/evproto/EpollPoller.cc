#include "EpollPoller.h"
#include "Channel.h"
//#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



namespace
{
 const int kNew = -1;
 const int kAdded = 1;
 const int kDeleted = 2;

}

namespace evproto
{
EPollPoller::EPollPoller(EventLoop* loop)
:Poller(loop),
loop_(loop),
epollfd_(::epoll_create(250)),
//ownerLoop_(loop),
events_(5)
{
//   cout<<"++++++++++   EPollPoller::EPollPoller   ++++++++++"<<endl;
}


EPollPoller::~EPollPoller()
{
::close(epollfd_);
}

Timestamp EPollPoller::poll(int timeoutMs,ChannelList* activeChannels)
{
	//struct epoll_event event2[20];
       //  int nfds = ::epoll_wait(epollfd_,event2,20,timeoutMs);
	//int nfds=::epoll_wait(epollfd_,event2,20,500);
	int nfds =::epoll_wait(epollfd_,&*events_.begin(),static_cast<int>(events_.size()),500);
	Timestamp time(Timestamp::now());
	int savedErrno = errno;
         if(nfds > 0)
	{
               //cout<<"---20200209---EpollPoller::epoll_wait_done"<<events_.size()<<endl;

		fillActiveChannels(nfds,activeChannels);
		/*
		if( implict_cast<size_t>(numEvents) == events_.size() )
		{
			events_.resize(events_.size()*2);
		}

		*/



	/*        
        int i = 0;
        int connfd,sockfd;
        struct sockaddr_in clientaddr;
        socklen_t clilen;
        int MAXLINE = 5;
        char line[MAXLINE];      
        struct epoll_event ev;
        int epfd;        
        ssize_t n;
        
       int listenfd;

        for(i=0;i<nfds;++i)
        {
	    cout<<"eventloop::LOOP1LOOP1"<<nfds<<endl;
            cout<<"eventloop::LOOP2LOOP2"<<events_.size()<<endl;

            cout<<"EPOLLPOLLER:::"<<events[i].data.fd<<":::"<<events[i].events<<endl;

            if(events[i].data.fd==listenfd)
            {
                connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
                if(connfd<0){
                    perror("connfd<0");
                    exit(1);
                }
                char *str = inet_ntoa(clientaddr.sin_addr);
                cout << "accapt a connection from " << str << endl;
                ev.data.fd=connfd;
                ev.events=EPOLLIN|EPOLLET;
                cout << "new connected" << endl;

                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN)
	    {
                cout << "EPOLLIN" << endl;
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
                cout << "read " << line << endl;
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

                cout << "OUT" << endl;
	
            }
         }
	*/
	}
	else if(nfds == 0){}
	else{}
	return time;
}


void EPollPoller::removeChannel(Channel* channel)
{

 // cout <<"----------EPollPoller::removeChannel-----000";
  Poller::assertInLoopThread();
  int fd = channel->fd();
//  LOG_TRACE << "fd = " << fd;
  assert(channels_.find(fd) != channels_.end());
  assert(channels_[fd] == channel);
  assert(channel->isNoneEvent());
  int index = channel->index();
  assert(index == kAdded || index == kDeleted);
  size_t n = channels_.erase(fd);
  (void)n;
  assert(n == 1);
  
 // cout <<"----------EPollPoller::removeChannel-----001";

  if (index == kAdded)
  {
    update(EPOLL_CTL_DEL, channel);
  }
  channel->set_index(kNew);


}

void EPollPoller::updateChannel(Channel* channel)
{
	Poller::assertInLoopThread();

        const int index = channel->index();
        
//	cout<<"EPollPoller::updateChaneel"<<index<<endl;

	if(index == kNew || index == kDeleted)
        {
                int fd = channel->fd();
                if(index == kNew)
                {			

			assert(channels_.find(fd) == channels_.end());
			
		       // cout<<"---3---  updateChannel:::"<< channel <<endl;
			
			channels_[fd] = channel;
     		}
                else
                {
			
			assert(channels_.find(fd) != channels_.end());
			assert(channels_[fd] = channel);
		}
		//cout<<"20200202EPollPoller::updatechannel::EPOLL_CTL_ADD"<<endl;
		channel->set_index(kAdded);
		update(EPOLL_CTL_ADD,channel);
	}
	else
	{
		update(EPOLL_CTL_MOD,channel);
        }

}
void EPollPoller::update(int operation,Channel* channel)
{
 struct epoll_event event;
 event.events = channel->events();
 event.data.fd = channel->fd();

 //cout<<"KINGKINGKING 20200212 EPollPoller::set::ptr"<<endl;

  event.data.ptr=channel;
 int fd = channel->fd();

 // cout << "20200202EPollPoller::update" << fd << endl;

 ::epoll_ctl(epollfd_,operation,fd,&event);
 



 // cout<<"123456789epoll_ctl add done op::"<< operationToString(operation) << "fd::" << fd  <<endl;
}

const char* EPollPoller::operationToString(int op)
{
switch(op)
{
 case EPOLL_CTL_ADD:
   return "ADD";
 case EPOLL_CTL_DEL:
   return "DEL";
 case EPOLL_CTL_MOD:
   return "MOD";
 default:
   return "unkonwn";

}

}



void EPollPoller::fillActiveChannels(int numEvents,ChannelList* activeChannels)
{

// cout<<"---20200209---EpollPoller::fillActiveChannels"<<numEvents<<endl;
   for (int i = 0; i < numEvents; ++i)
  {

    
 //cout<<"---20200209---EpollPoller::fillActiveChannels"<<numEvents<<endl;
    /*
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    int fd = channel->fd();
    ChannelMap::const_iterator it = channels_.find(fd);
   // assert(it != channels_.end());
   // assert(it->second == channel);
    
    channel->set_revents(events_[i].events);
    activeChannels->push_back(channel);
    */



   Channel* channel = static_cast<Channel*>(events_[i].data.ptr);

  //  Channel channel = (*static_cast<Channel*>(events_[i].data.ptr));
    
/*
    cout<< "CCC111 " << static_cast<Channel*>(events_[i].data.ptr) << endl;
    

    cout<< "CCC222" << &(*static_cast<Channel*>(events_[i].data.ptr)) << endl;

     cout << "CCC333" << (events_[i].data.ptr) << endl;

     cout << "CCC444" << (Channel*)(events_[i].data.ptr) << endl;

   /// cout<<"---20200209---fill"<<event2[i].data.fd<<":::"<<event2[i].events<<endl;
    
//    cout<<"---20200209---"<<&channel<<endl;
*/
   // Channel* channel = new Channel(loop_,event2[i].data.fd);
    int fd = channel->fd();
    ChannelMap::const_iterator it = channels_.find(fd);
     
//     cout<<"EpollPoll::fill+++" <<  fd << "OOO" << channels_.size() << endl; ;    

     map<int,Channel*>::iterator iter;
     iter = channels_.begin();
     while(iter != channels_.end())
     {
//	cout<< "*** 20200210 *** channel trace"<<iter->first<<"D5D5D5"<<iter->second<<endl;
        iter++;

     }
  //  cout<<channel<<endl;

    assert(it != channels_.end());
  //  cout<<channel<<it->second<<endl;

    assert(it->second == channel);

    channel->set_revents(events_[i].events);


//     cout << "POLLIN | POLLPRI | POLLRDHUP:::" <<( POLLIN | POLLPRI | POLLRDHUP) << "POLLOUT:::"<< POLLOUT << endl;

   //   if((event2[i].events) & (POLLIN | POLLPRI | POLLRDHUP) ){cout<<"INININ"<<endl;}

 //     if((event2[i].events) & (POLLOUT) ){cout<<"OOUTOUTOUT"<<endl;}

//      channel->set_revents(events_[i].events);

///    cout<<"20200210::EPollPoller::fillActiveChannels"<<endl;

//  cout<<"---20200209---epollpoller::set_revents"<<event2[i].events<<endl;
    activeChannels->push_back(channel);

  } 

}



}

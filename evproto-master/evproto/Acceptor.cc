#include "Acceptor.h"
#include <string.h>
//#include <sys/socket.h>
#include <arpa/inet.h>



#define LISTENQ 20

namespace evproto
{
Acceptor::Acceptor(EventLoop* loop)
:acceptSocket_(::socket(AF_INET,SOCK_STREAM,0)),
loop_(loop),
acceptChannel_(loop,acceptSocket_),
listenning_(false)
{
//    cout<<"20200202Acceptor::Acceptor::Channel::"<<acceptChannel_<<endl;
    int portnumber = 2002;

    
    //maxi = 0;
    //acceptSocket_ = socket(AF_INET,SOCK_STREAM,0);
    //bind
    struct sockaddr_in serveraddr;
//     sockaddr_in serveraddr;





    int optval = 1;

    ::setsockopt(acceptSocket_,SOL_SOCKET,SO_REUSEADDR,&optval,static_cast<socklen_t>(sizeof optval));

    ::setsockopt(acceptSocket_,SOL_SOCKET,SO_REUSEPORT,&optval,static_cast<socklen_t>(sizeof optval));





    
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    char *local_addr="127.0.0.1";
    if(inet_aton(local_addr,&(serveraddr.sin_addr))<=0)//htons(portnumber);
    {
       cout<<"inet_aton fail"<<endl;
    }
    else
    {
       cout<<"inet_aton success"<<endl;
     }

    serveraddr.sin_port=htons(portnumber);
    if(bind(acceptSocket_,(sockaddr *)&serveraddr,sizeof(serveraddr))<0)
    {
       cout<<"bind fail"<<endl;
    }
    else
   {
        cout<<"bind success"<<endl;
   }
    /*
    //listen(listenfd,LISTENQ);
    if(::listen(acceptSocket_ , LISTENQ)<0)
    {
     cout<<"listen fail"<<endl;
    }
    else
    {
     cout<<"listen success"<<endl;
    }
    */

    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead,this));    
    

    cout<<"123456789bind done"<<endl;  

}

Acceptor::~Acceptor()
{}

void Acceptor::listen()
{
	cout << "Acceptor::listen" << loop_->getThreadId() <<endl;
	loop_->assertInLoopThread();
        listenning_=true;
	//::listen(acceptSocket_,LISTENQ);
        if(::listen(acceptSocket_ , LISTENQ)<0)
	{
	    cout<<"listen fail"<<endl;
        }
	else
	{
	    cout<<"listen success"<<endl;
        }
	acceptChannel_.enableReading();
        cout << "20200202Acceptor::listen"<<endl;
	//listen(acceptSocket_,20);
	//acceptSocket_.listen();
}


void Acceptor::handleRead()
{
	cout<<"---4---Acceptor::handleRead"<<endl;
	loop_->assertInLoopThread();
	//acceptSocket_.accept();
	//struct sockaddr_in clientaddr;

	struct sockaddr_in clientaddr;


	socklen_t clilen;
        int connfd;
	connfd = accept(acceptSocket_,(sockaddr *)&clientaddr,&clilen);
        cout<< "20200202Acceptor::handleRead"<<endl;
        if(connfd >= 0)
        {
	    if(newConnectionCallback_)
	    {
		newConnectionCallback_(connfd,clientaddr);
		cout<<"newConnectionCallback success"<< connfd  << "addr" << inet_ntoa(clientaddr.sin_addr) <<endl;
	    }
	    else
            {
	         cout<<"newConnectionCallback fail"<<endl;
            }
	    cout<<"connectionCallback SUCCESS"<<endl;
        }
	else
	{
	   cout<<"connectionCallback FAIL"<<endl;
	}


}

}

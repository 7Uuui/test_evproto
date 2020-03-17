#include "examples/sudoku.pb.h"
#include "evproto/eventloop.h"
#include "evproto/evproto.h"
#include "evproto/TcpClient.h"
#include "evproto/Channel.h"
#include "evproto/some_func.h"
//#include "evproto/rpcchannel.h"
//#include "evproto/rpccontroller.h"

#include "testTime/TimeStamp.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <iostream>
using namespace std;
using namespace evproto;
using namespace std::placeholders;

class RpcClient
{
public:
 RpcClient(EventLoop* loop,const sockaddr_in& listenAddr):
 loop_(loop),
 client_(loop,listenAddr,"EchoClient")
 {
    client_.setConnectionCallback(std::bind(&RpcClient::onConnection,this,_1));

//    client_.setMessageCallback(std::bind(&RpcClient::onMessage,this,_1,_2,_3));

    client_.setMessageCallback(std::bind(&RpcClient::onMessage,this,_1,_2));

 }
 void connect()
 {
    client_.connect();
 }
private:


  void onMessage(const TcpConnectionPtr& conn,char* msg)
  {

//char *msg_left = substring(msg,0,strlen(msg)-1);

//char *msg_oldstr = substring(msg,strlen(msg)-1,1);

char *msg_left = substring(msg,0,5);

char *msg_oldstr = substring(msg,5,strlen(msg)-5);

int msg_oldright = atoi(msg_oldstr);

char *msg_newright;
//cout<<"crush::"<<msg<<"left::"<<msg_left<<"msgstr" << msg_oldstr << "--"<< msg_oldright<<"msg_oldright"<<msg_oldright <<endl;
sprintf(msg_newright,"%d",(msg_oldright+1));

strcat(msg_left,msg_newright);
conn->send(msg_left);
cout << "CLIENT_SEND_ROUND"<<msg<<".."<<msg_left<<endl;

  }

  void onConnection(const TcpConnectionPtr& conn)
  {
    //cout<<"2.0.2.0.0.2.2.1.--------++++++++++++--------send"<<endl;
      cout << " connect success:::FirstRound " << endl;
     if (conn->connected())
    {
      cout<< "client::onConnection::name::" << (conn->name()).c_str() << endl;
      conn->send("hello0");
      /*
      cout<<"---CCC---"<<"CLIENT CONNECTED"<<endl;
      //channel_.reset(new RpcChannel(conn));
      channel_->setConnection(conn);
      sudoku::SudokuRequest request;
      request.set_checkerboard("001010");
      sudoku::SudokuResponse* response = new sudoku::SudokuResponse;

      stub_.Solve(NULL, &request, response, NewCallback(this, &RpcClient::solved, response));
      */
    }
    else
    {
      loop_->quit();
    }


  }


  EventLoop* loop_;
  TcpClient client_;
 
};
/*

class RpcClient 
{
 public:
  RpcClient(EventLoop* loop, const InetAddress& serverAddr)
    : loop_(loop),
      client_(loop, serverAddr, "RpcClient"),
      channel_(new RpcChannel),
      stub_(get_pointer(channel_))
  {
    client_.setConnectionCallback(
        std::bind(&RpcClient::onConnection, this, _1));
    
    //client_.setMessageCallback(
      //  std::bind(&RpcChannel::onMessage, get_pointer(channel_), _1, _2, _3));
    
    client_.setMessageCallback(
        std::bind(&RpcChannel::onMessage, get_pointer(channel_), _1));

   // client_.enableRetry();
  }

  void connect()
  {
    client_.connect();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    cout<<"rpcclient::onConnection"<<endl;

    if (conn->connected())
    {

      cout<<"---CCC---"<<"CLIENT CONNECTED"<<endl;
      //channel_.reset(new RpcChannel(conn));
      channel_->setConnection(conn);
      sudoku::SudokuRequest request;
      request.set_checkerboard("001010");
      sudoku::SudokuResponse* response = new sudoku::SudokuResponse;

      stub_.Solve(NULL, &request, response, NewCallback(this, &RpcClient::solved, response));
    }
    else
    {
      loop_->quit();
    }
  }

  void solved(sudoku::SudokuResponse* resp)
  {
    LOG_INFO << "solved:\n" << resp->DebugString();
    client_.disconnect();
  }

  EventLoop* loop_;
  TcpClient client_;
  RpcChannelPtr channel_;
  sudoku::SudokuService::Stub stub_;
}
*/


void solved(sudoku::SudokuResponse* resp)
{
  cout << "CLIENT::"<< resp->solved() << endl;
}
/*
int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);


  evproto::EventLoop loop;
  evproto::RpcChannel channel(&loop);
  CHECK(channel.addServer("127.0.0.1", 2002));
  sudoku::SudokuService::Stub stub(&channel);
  cout << "CLIENT::" << stub.GetDescriptor()->name() << endl;
  cout << "CLIENT::" << stub.GetDescriptor()->full_name() << endl;

  evproto::RpcController controller;
  sudoku::SudokuRequest req;
  req.set_checkerboard("1312313.312");
  sudoku::SudokuResponse resp;
  TimeStamp time;
  string str_time = time.toFormattedString();
  stub.Solve(&controller, &req, &resp, evproto::gpb::NewCallback(solved, &resp));
  loop.loop();
}
*/


int main(int argc,char* argv[])
{
EventLoop loop;
//RpcClient rpcClient(&loop);
//InetAddress serverAddr;
sockaddr_in mysock;
bzero(&mysock,sizeof(mysock));
mysock.sin_family = AF_INET;
mysock.sin_port = htons(2002);
mysock.sin_addr.s_addr = inet_addr("127.0.0.1");

char buf[32];
//RpcClient rpcClient(&loop,mysock,buf);

RpcClient rpcClient(&loop,mysock);

rpcClient.connect();
loop.loop();
}

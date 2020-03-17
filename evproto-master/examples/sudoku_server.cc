#include "examples/sudoku.pb.h"

#include "evproto/evproto.h"
#include "evproto/eventloop.h"
//#include "evproto/httpserver.h"
//#include "evproto/rpcserver.h"
#include "evproto/rpcserver.h"
#include "evproto/TcpConnection.h"
#include "evproto/some_func.h"


#include <glog/logging.h>
#include <functional>


#include "testTime/TimeStamp.h"
//cout
#include <string>
#include <iostream>
using namespace std;
using namespace evproto;
/*
namespace sudoku
{

class SudokuServiceImpl : public SudokuService
{
 public:
  virtual void Solve(::google::protobuf::RpcController* controller,
                       const ::sudoku::SudokuRequest* request,
                       ::sudoku::SudokuResponse* response,
                       ::google::protobuf::Closure* done)
  {

    TimeStamp time;
    string str_time = time.toFormattedString();
    cout << "SERVICE::solved" << endl;
    response->set_solved(true);
    done->Run();
  }
};

}
*/
class SudokuServer
{
public:
 SudokuServer(evproto::EventLoop* loop,int numThreads)
:server_(loop,numThreads)
{
//server_.setConnectionCallback(std::bind(&SudokuServer::onConnection,this,_1)); 

server_.setMessageCallback(std::bind(&SudokuServer::onMessage,this,_1,_2)); 
}

void start()
{
server_.start();
}

void onConnection(const TcpConnectionPtr& conn)
{
cout<<"S.E.R.V.E.R.O.N.C.O.N.N.E.C.T.I.O.N"<<endl;

}
void onMessage(const TcpConnectionPtr& conn,char* msg)
{
// const char* msg = "hhhh";
//char *msg_left ;
//char *msg_right;
//msg_left=left(msg_left,msg,strlen(msg)-1);

//msg_right=right(msg_right,msg,1);

//int msg_oldright = atoi(substr(msg,-1));


//char *msg_left = substring(msg,0,strlen(msg)-1);
//char *msg_right = substring(msg,strlen(msg)-1,1);

char *msg_left = substring(msg,0,5);
char *msg_right = substring(msg,5,strlen(msg)-5);


//char *msg_right2 = substring(msg,strlen(msg)-2,1);

int msg_oldright = atoi(msg_right);

char *msg_newright;
int n = sprintf(msg_newright,"%d",(msg_oldright+1));

//cout<<"str_left::"<<msg_left<<"str_right::"<<msg_right<<"int_right_old::"<<msg_oldright<<"int_right_new"<<msg_newright<<":::"<<msg_right2<<endl;


strcat(msg_left,msg_newright);

//cout << "Server::sendMsg +++ " << msg << "connName::" << conn->name() << endl;
 conn->send(msg_left);

  cout<<"SERVER_SEND_ROUND"<<msg<<".."<<msg_left<<endl;
}
private:
evproto::RpcServer server_;
};

int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);

  /*
  evproto::EventLoop loop;
  evproto::HttpServer httpServer(&loop, 2000);
  evproto::RpcServer rpcServer(&httpServer);
  sudoku::SudokuServiceImpl sudokuService;
  rpcServer.registerService(&sudokuService);

  cout << "SERVICE::loop" << endl;
  int ret = loop.loop();
  //LOG(INFO) << "EventLoop::loop() returns " << ret;
  */
  cout << "RpcServer Enty" << endl; 
//  evproto::RpcServer rpcServer();//bc
 // evproto::RpcServer rpcServer;
   

   evproto::EventLoop loop;
  // evproto::RpcServer rpcServer(&loop,2000);
   SudokuServer server(&loop,2000);


/*
//  sudoku::SudokuServiceImpl sudokuService;
// rpcServer.registerService(&sudokuService);   
 */
//   rpcServer.start();
   server.start();
   int ret = loop.loop();

}


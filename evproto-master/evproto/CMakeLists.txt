add_definitions(-std=c++11  -pthread  -lpthread)

set(evproto_SRCS
  Acceptor.cc
  Channel.cc
  Poller.cc
  EpollPoller.cc
  eventloop.cc
  EventLoopThread.cc
  EventLoopThreadPool.cc
  evproto.cc
  rpcchannel.cc
  rpccontroller.cc
  # rpcserver.cc
  rpcserver.cc
  Timestamp.cc 
  Thread.cc
  CurrentThread.cc
  CountDownLatch.cc
  TcpConnection.cc
  TcpClient.cc
  Connector.cc
  )

include_directories(${PROJRCT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)

add_library(evproto ${evproto_SRCS})


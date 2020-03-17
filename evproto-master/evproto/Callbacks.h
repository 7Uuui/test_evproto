#ifndef CALLBACKS_H
#define CALLBACKS_H


#include "Timestamp.h"

#include <functional>
#include <memory>


namespace evproto
{

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;


template<typename T>
inline T* get_pointer(const std::shared_ptr<T>& ptr)
{
  return ptr.get();
}

template<typename T>
inline T* get_pointer(const std::unique_ptr<T>& ptr)
{
  return ptr.get();

}
class Buffer;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void()> TimerCallback;
typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;
typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;
typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
//typedef std::function<void (const TcpConnectionPtr&,Buffer*,Timestamp)> MessageCallback;
typedef std::function<void (const TcpConnectionPtr&,char*)> MessageCallback;


void defaultConnectionCallback(const TcpConnectionPtr& conn);
//void defaultMessageCallback(const TcpConnectionPtr& conn,Buffer* buffer,Timestamp receiveTime);

void defaultMessageCallback(const TcpConnectionPtr& conn,char*);
//typedef std::function<void(const TcpConnectionPtr&,size_t)> ConnectionCallback;





}
#endif

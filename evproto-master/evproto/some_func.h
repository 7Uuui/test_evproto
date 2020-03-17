#ifndef SOMEFUNC_H
#define SOMEFUNC_H
#include <string.h>
#include <netinet/in.h>
#include <errno.h>

namespace evproto
{
inline void memZero(void* p ,size_t n)
{
    memset(p,0,n);
}
/*
const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr)
{
 return static_cast<const struct sockaddr*>(implict_cast<const void*>(addr));
}
struct sockaddr* sockaddr_cast(struct sockaddr_in6* addr)
{
 return static_cast<struct sockaddr*>(implict_cast<void*>(addr));
}
const struct sockaddr*   sockaddr_cast(const struct sockaddr_in* addr)
{
return static_cast<const struct sockaddr*>(implict_cast<const void*>(addr));
} 


*/

inline struct sockaddr_in getLocalAddr(int sockfd)
//struct sockaddr_in getLocalAddr(int sockfd)
{
 struct sockaddr_in localaddr;
 memZero(&localaddr,sizeof localaddr);
 socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
  //if(::getsockname(sockfd,sockaddr_cast(&localaddr),&addrlen) <0)
   if(::getsockname(sockfd,(struct sockaddr *)&localaddr,&addrlen) < 0)
  {}
  return localaddr;

}

inline struct sockaddr_in getPeerAddr(int sockfd)
{
 struct sockaddr_in peeraddr;
 memZero(&peeraddr,sizeof peeraddr);
 socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
//  if(::getpeername(sockfd,sockaddr_cast(&peeraddr),&addrlen) <0)
  if(::getpeername(sockfd,(struct sockaddr *)&peeraddr,&addrlen) < 0)
  {}
  return peeraddr;

}
/*
inline char* left(char *dst,char *src,int n)
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n=len;
    //p += (len-n);
    //while(*(q++)=*(p++));
      while(n--) *(q++)=*(p++);
      *(q++)='\0';
    return dst;
}
*/
inline char* substring(char* ch, int pos,int length)
{
	char* pch = ch;
	char* subch=(char*)calloc(sizeof(char),length+1);
	int i;
	pch=pch+pos;
	for(i=0;i<length;i++){subch[i]=*(pch++);}
	subch[length]='\0';
	return subch;

}
inline char* right(char *dst,char *src,int n)
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n=len;
    p += (len-n);
    while(*(q++)=*(p++));
    return dst;
}


  inline ssize_t
  my_read(int fd, void *vptr, size_t n){ // , int *errnop, bool *eofp) {
    int *errnop;
    bool *eofp;
    size_t nleft = n;
    ssize_t nread;
    char *ptr = (char *)vptr;

    while (nleft > 0) {
      if ((nread = ::read(fd, ptr, nleft)) < 0) {
        if (errno == EINTR) {
          nread = 0; /* and call read() again */
          continue;
        }
        *errnop = errno;

        if (*errnop == EAGAIN || nleft < n)
          break;     /* already read something, most likely EAGAIN */

        return -1;   /* other errors and nothing read */
      }
      else if (nread == 0) {
        *eofp = true;
        break;
      }

      nleft -= nread;
      ptr   += nread;
    }
    cout << "some_func:::myread" << (n-nleft) << endl;

    return n - nleft;
  }
/*
  ssize_t
  my_write(int fd, const iovec *vector, int count){ // , int *errnop) {
    ssize_t nwritten;
    while ((nwritten = ::writev(fd, vector, count)) <= 0) {
      if (errno == EINTR) {
        nwritten = 0; // and call write() again 
        continue;
      }
      *errnop = errno;
      return -1;
    }
    return nwritten;
  }


*/

inline int my_write(int fd,const void *buffer,int length)
{

 int bytes_left;
 int written_bytes;
//char *ptr = buffer;
 void* ptr_=const_cast<void*>(buffer);
  char* ptr = static_cast<char*>(ptr_);
 bytes_left=length;
 while(bytes_left>0)
 {
  written_bytes=write(fd,ptr,bytes_left);
  if(written_bytes <= 0)
  {
    if(errno == EINTR){written_bytes = 0;}
    else{return(-1);}
  }
  bytes_left-=written_bytes;
  ptr+=written_bytes;
 }
 return(0);
}
/*//0309
inline int my_read(int fd,void *buffer,int length)
{

 int bytes_left;
 int bytes_read;
 char *ptr;
 bytes_left=length;
 while(bytes_left>0)
 {
  bytes_read=write(fd,ptr,bytes_read);
  if(bytes_read <= 0)
  {
    if(errno == EINTR){bytes_read = 0;}
    else{return(-1);}
  }
  else if(bytes_read == 0)
     break;
  bytes_left-=bytes_read;
  ptr+=bytes_read;
 }
 return(length-bytes_left);
}
*/
inline bool isSelfConnect(int sockfd)
{
// struct sockaddr_in6 localaddr = getLocalAddr(sockfd);
// struct sockaddr_in6 peeraddr = getPeerAddr(sockfd);
/*
//  struct sockaddr_in serv ,guest ;
   struct sockaddr_in localaddr,peeraddr;
  socklen_t serv_len = sizeof(serv);
  socklen_t guest_len = sizeof(guest);

  */ 
   struct sockaddr_in localaddr,peeraddr;
   socklen_t serv_len = sizeof(localaddr);
   socklen_t guest_len = sizeof(peeraddr);

  getsockname(sockfd,(struct sockaddr *)&localaddr,&serv_len);
  getpeername(sockfd,(struct sockaddr *)&peeraddr,&guest_len);


  

/*
 if(localaddr.sin6_family == AF_INET)
 {
   const struct sockaddr_in* laddr4 = reinterpret_cast<struct sockaddr_in*>(&localaddr);

   const struct sockaddr_in* rddr4 = reinterpret_cast<struct sockaddr_in*>(&peeraddr);

   return laddr4->sin_port == raddr4->sin_port
     &&  laddr4->sin_addr.s_addr == raddr4->sin_addr.s_addr;
 
   
 }

 else if(localaddr.sin6_family == AF_INET6)
 {
   return localaddr.sin6_port == peeraddr.sin6_port
     &&  memcmp(&localaddr.sin6_addr, &peeraddr.sin6_addr,sizeof localaddr.sin6_add) == 0;
 }
 else
 {
   return false;
 }
*/
return localaddr.sin_addr.s_addr == peeraddr.sin_addr.s_addr 
&& localaddr.sin_port == peeraddr.sin_port;
};
}

#endif

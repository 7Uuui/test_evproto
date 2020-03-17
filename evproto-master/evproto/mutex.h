#include <pthread.h>



namespace Internal
{
class MutexLock
{
public:
  MutexLock()
  {
     pthread_mutex_init(&mutex,NULL);
   }
  ~MutexLock()
  {
     pthread_mutex_destroy(&mutex);
  }
  void lock()
  {
     pthread_mutex_lock(&mutex);
  }
  
  void unlock()
  {
     pthread_mutex_unlock(&mutex);
  }

private:
   pthread_mutex_t mutex;

};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock& mutex): mutex_(mutex)
    { mutex_.lock();}
    
    ~MutexLockGuard()
    { mutex_.unlock();}

private:
     MutexLock& mutex_;

};

}

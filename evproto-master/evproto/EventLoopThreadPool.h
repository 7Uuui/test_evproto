#include <vector>
#include <memory>
using namespace std;


namespace evproto
{

 class EventLoop;

 class EventLoopThread;

 class EventLoopThreadPool
 {
   public:
      typedef std::function<void(EventLoop*)> ThreadInitCallback;
      EventLoopThreadPool(EventLoop* baseLoop);
      ~EventLoopThreadPool();
       void start(const ThreadInitCallback& cb = ThreadInitCallback());
        EventLoop* getNextLoop();
    private:
      string name_;
      bool started_;
      EventLoop* baseLoop_;
      int next_;
      int numThreads_;
      std::vector<std::unique_ptr<EventLoopThread>> threads_;
      std::vector<EventLoop*> loops_;
 };

}

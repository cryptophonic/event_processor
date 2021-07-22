#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

struct ThreadJob {
  int priority;
  void* data;
};

struct CompareTasks {
  bool operator()(ThreadJob const& t1, ThreadJob const& t2) {
    // return true for smaller priorities
    return t1.priority < t2.priority;
  }
};

class ThreadPool {
public:
  ThreadPool();
  ~ThreadPool();
  
  void AddHandler(void (*)(void*));
  void AddJob(ThreadJob&);
  
private:
  static vector<thread> pool;
  static mutex poolMutex;
  static condition_variable cond;
  static bool terminate;
  
  static void processing_loop(int);
  
  static priority_queue<ThreadJob, vector<ThreadJob>, CompareTasks> queue;
  static void (*handler)(void*);
};
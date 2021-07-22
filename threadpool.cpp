#include <iostream>

#include "threadpool.h"

vector<thread> ThreadPool::pool;
mutex ThreadPool::poolMutex;
condition_variable ThreadPool::cond;
bool ThreadPool::terminate = false;
priority_queue<ThreadJob, vector<ThreadJob>, CompareTasks> ThreadPool::queue;
void (*ThreadPool::handler)(void*);

ThreadPool::ThreadPool() {
  int numThreads = thread::hardware_concurrency();
  
  cout << "Starting " << numThreads << " threads" << endl;
  
  for (int i=0; i<numThreads; i++) {
    pool.push_back(thread(processing_loop, i));
  }
}

ThreadPool::~ThreadPool() {
  {
    unique_lock<mutex> guard(poolMutex);
    terminate = true;
  }
  
  cout << "Shutting down thread pool" << endl;
  cond.notify_all();
  
  for (thread &t: pool) {
    t.join();
  }
  
  pool.clear();
}

void ThreadPool::AddHandler(void (*h)(void*)) {
  handler = h;
}

void ThreadPool::AddJob(ThreadJob& task) {
  {
    unique_lock<mutex> guard(poolMutex);
    queue.push(task);
  }
  cond.notify_one();
}

void ThreadPool::processing_loop(int num) {
  cout << "  thread " << num << " started" << endl;
  while (!terminate) {
    ThreadJob job;
    {
      unique_lock<mutex> guard(poolMutex);
      cond.wait(guard);
      job = queue.top();
      queue.pop();
    }
    if (!terminate) {
      // do work
      handler(job.data);
    }
  }
}
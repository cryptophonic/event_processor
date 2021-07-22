#include <iostream>

#include "events.h"
#include "threadpool.h"

using namespace std;

// This function is called by the worker thread that 
// picks up the task. The big assumption made here is the 
// library we're calling is thread safe.
void doTask(void* task) {
  if (!TS_processTask((const TS_TASK_T*)task)) {
    // It was not specified what to do with a failed task. 
    // Assuming no error processing or re-queueing of tasks.
  }
  free(task);
}

int main() {
  // Create thread pool
  ThreadPool pool;
  pool.AddHandler(&doTask);
  
  // Register for events
  // not implemented
  
  // This thread becomes the event listener
  while (true) {
    EL_EVENT_T* event = EL_getNextEvent();
    if (event != NULL) {
      // got the event, generate the task!
      TS_TASK_T* task = (TS_TASK_T*) malloc(sizeof(TS_TASK_T));
      if (EH_processEvent(event, task)) {
        ThreadJob tj;
        tj.priority = task->taskPriority;
        tj.data = task;
        pool.AddJob(tj);
      }
    }
    
    // sleep for a bit between calls
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  
  return 0;
}
#define EVENT_DATA_MAX_SIZE 1000
typedef struct {
  unsigned int eventSeq;    // unique event sequence (starts with 1 
                            // and increments by 1 for each consecutive 
                            // event) 
  unsigned int eventId;	    // event ID (identifies the event)
  unsigned int dataLen;     // event data length in Bytes
  char data[EVENT_DATA_MAX_SIZE];
} EL_EVENT_T;

#define TS_TASK_LIST_MAX_SIZE	 1000
typedef struct {
	  unsigned int taskPriority;	// 0 = highest
	  unsigned int taskId;
} TS_TASK_T;

/*! Get next event
  \return pointer to next pending event,
    NULL if no events pending
*/
EL_EVENT_T* EL_getNextEvent();

/*! Process event and generate task     
  \param event 		pointer to event to process
  \param task	    pointer to task structure
  \return bool 		true, if event was processed and task was generated 
                  successfully 
*/
bool EH_processEvent(const EL_EVENT_T  *const event, TS_TASK_T *const task);

/*! Process task
  \param task		  pointer to task
  \return bool 		true, if success, false else
*/
bool TS_processTask(const TS_TASK_T *const task);

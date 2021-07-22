#include <cstddef>

#include "events.h"

EL_EVENT_T* EL_getNextEvent() {
  return NULL;
}

bool EH_processEvent(const EL_EVENT_T  *const event, TS_TASK_T *const task) {
  return false;
}

bool TS_processTask(const TS_TASK_T *const task) {
  return false;
}

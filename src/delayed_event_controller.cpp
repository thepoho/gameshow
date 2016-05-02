#include "delayed_event_controller.h"



DelayedEventController::DelayedEventController()
{
  
}

DelayedEventController::~DelayedEventController()
{
}

void DelayedEventController::startup()
{
  //Generate all my blank delayed events and put them in a freelist.
  WrappedEvent* pRoot = new WrappedEvent[MAX_DELAYED_EVENT_COUNT];
  
  //die if we can't allocate memory for our freelist
  assert(NULL != pRoot);

  //set all the next pointers
  for(int i=0; i < MAX_DELAYED_EVENT_COUNT-1; i++){
    pRoot[i].pNext = &pRoot[i+1];
  }
  pRoot[MAX_DELAYED_EVENT_COUNT-1].pNext = NULL;

  freeList = pRoot;
  activeList = NULL;
}

void DelayedEventController::update(unsigned int delta)
{
  elapsedTime += delta;
  //check to see if any delayed events are required to be run and run them. Then move them back to the freelist  
}

void DelayedEventController::createEvent(string event_type, unsigned int trigger_time, string data)
{
  WrappedEvent *newEvent = freeList;
  assert(NULL != newEvent);

  freeList        = freeList->pNext;
  newEvent->pNext = activeList;
  activeList      = newEvent;
}


DelayedEvent* DelayedEventController::getDueEvent()
{
  WrappedEvent *tmp = activeList;
  while(NULL != tmp){
    if(activeList->delayed_event.getTriggerTime() < elapsedTime){
      return(&tmp->delayed_event);
    }
    tmp = tmp->pNext;
  }
  return NULL;
}


void DelayedEventController::freeEvent(DelayedEvent *event)
{
  //remove *event from the active list and put it back into the free list
}

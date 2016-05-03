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
    //freelist doesnt care about prev pointers so dont bother initializing
  }
  pRoot[MAX_DELAYED_EVENT_COUNT-1].pNext = NULL;

  freeList = pRoot;
  activeList = NULL;

  cout << "Delayed Event Controller started up" << endl;
}

void DelayedEventController::update(unsigned int delta)
{
  elapsedTime += delta;
  //check to see if any delayed events are required to be run and run them. Then move them back to the freelist  
}

void DelayedEventController::createEvent(string event_type, unsigned int trigger_time, string data)
{
  //TODO: Ensure this event doesn't already exist!

  WrappedEvent *newEvent = freeList;
  assert(NULL != newEvent);

  //make free list pointer be the next available free thing
  freeList        = freeList->pNext;


  //set previous pointer on the next event to be my new event
  if(NULL != activeList){
    activeList->pPrevious = newEvent;
  }

  //set the 'next' pointer on my new event to the start of the active list
  newEvent->pNext       = activeList;

  newEvent->event.startup(event_type, trigger_time, data);
  //cout << "Created event " << event_type << " with trigger time of " << trigger_time << endl;

  //make the active list start on my new event.
  activeList = newEvent;
}


DelayedEvent* DelayedEventController::getDueEvent()
{
  WrappedEvent *tmp = activeList;
  while(NULL != tmp){
    if(tmp->event.getTriggerTime() < elapsedTime){
      return(&tmp->event);
    }
    tmp = tmp->pNext;
  }
  return NULL;
}


void DelayedEventController::freeEvent(DelayedEvent *event)
{
  WrappedEvent *tmp = findWrappedEvent(event);
  if(NULL != tmp){

    //remove *event from the active list and put it back into the free list
    if(tmp == activeList){
      //we are the tip of the active list
      activeList = tmp->pNext;
    }else{
      tmp->pPrevious->pNext = tmp->pNext;
    }

    tmp->pPrevious = NULL;
    tmp->pNext     = freeList;
    freeList       = tmp;
  }else{
    cout << "Could not find wrapped event to free" << endl;
  }
}

DelayedEventController::WrappedEvent *DelayedEventController::findWrappedEvent(DelayedEvent *event)
{
  WrappedEvent *tmp = activeList;
  while(NULL != tmp){
    if(&tmp->event == event){
      return(tmp);
    }
    tmp = tmp->pNext;
  }
  return NULL;
}

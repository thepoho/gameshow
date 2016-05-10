#ifndef _DELAYED_EVENT_CONTROLLER_H
#define _DELAYED_EVENT_CONTROLLER_H

#include "delayed_event.h"
#include "socket_server.h"

class DelayedEventController
{
public:
  DelayedEventController();
  ~DelayedEventController();

  void update(unsigned int delta);

  void startup();
  void createEvent(string event_type, unsigned int trigger_time, string data);


  DelayedEvent* getDueEvent();
  void freeEvent(DelayedEvent *event);

private:
 struct WrappedEvent {
   DelayedEvent  event;
   WrappedEvent* pNext;
   WrappedEvent* pPrevious;
 };
 WrappedEvent* findWrappedEvent(DelayedEvent *event);
 
 WrappedEvent* freeList; 
 WrappedEvent* activeList; 
  
 WrappedEvent* pRoot;
 //DelayedEvent* delayed_events[MAX_DELAYED_EVENT_COUNT];
 //DelayedEvent* delayed_events_freelist[MAX_DELAYED_EVENT_COUNT];


 unsigned int elapsedTime;
};

#endif //DELAYED_EVENT_CONTROLLER_H

#ifndef _DELAYED_EVENT_H
#define _DELAYED_EVENT_H

#include "common_defines.h"


class DelayedEvent
{
public:
  DelayedEvent();
  ~DelayedEvent();
 
  void startup(string _event_type, unsigned int _trigger_time, string _data);

  string getEventType() { return(event_type); }
  unsigned int getTriggerTime() { return(trigger_time); }

private:
  string event_type;
  unsigned int trigger_time;
  string data;
};

#endif //_DELAYED_EVENT_H

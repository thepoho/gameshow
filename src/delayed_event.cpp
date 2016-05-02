#include "delayed_event.h"

DelayedEvent::DelayedEvent()
{
}

DelayedEvent::~DelayedEvent()
{
}

void DelayedEvent::startup(string _event_type, unsigned int _trigger_time, string _data)
{
  event_type = _event_type;
  trigger_time = _trigger_time;
  data = _data;
}

/*
void DelayedEvent::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String(name.c_str());
  writer->String("num");
  writer->Uint(num);
  writer->String("row");
  writer->Uint(row);
  writer->String("col");
  writer->Uint(col);
  writer->String("state");
  writer->Uint(state);
  writer->EndObject();
}
*/

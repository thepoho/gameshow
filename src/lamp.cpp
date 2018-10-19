#include "lamp.h"

Lamp::Lamp()
{
}

Lamp::~Lamp()
{
}

void Lamp::startup(int _row, int _col, int _num, string _name)
{
  row   = _row;
  col   = _col;
  name  = _name;
  num   = _num;
  state = LAMP_OFF;//default to off
 // cout << "creating Lamp " << row << ", " << col << ", " << name << ", " << num << endl;
}

void Lamp::serializeJson(Writer<StringBuffer>* writer)
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

bool Lamp::setState(LampState _newState)
{
  //returns true if state changed
  bool ret = false;
  if(state != _newState){
    ret = true;
  }
  state = _newState;
  return(ret);
}

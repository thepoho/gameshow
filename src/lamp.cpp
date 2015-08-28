#include "lamp.h"

lamp::lamp()
{
}

lamp::~lamp()
{
}

void lamp::startup(int _row, int _col, int _num, string _name)
{
	row   = _row;
	col   = _col;
  name  = _name;
  num   = _num;
  state = LAMP_FLASH_FAST;//default to flash fast!
//  cout << "creating lamp " << row << ", " << col << ", " << name << ", " << num << endl;
}

void lamp::serializeJson(Writer<StringBuffer>* writer)
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

bool lamp::setState(LampState _newState)
{
  //returns true if state changed
  bool ret = false;
  if(state != _newState){
    ret = true;
  }
  state = _newState;
  return(ret);
}
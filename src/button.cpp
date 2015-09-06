#include "button.h"

button::button()
{
  onOffState = 0;
}

button::~button()
{
}

void button::startup(int _row, int _col, int _num, string _name)
{
  row = _row;
  col = _col;
  name = _name;
  num = _num;
  // state = button_ON;//default to on
  cout << "creating button " << row << ", " << col << ", " << name << ", " << num << endl;
}

bool button::setState(int _newState)
{
  //returns true if state changed
  bool ret = false;
  if(onOffState != _newState){
    ret = true;
  }
  onOffState = _newState;
  return(ret);
}

void button::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String(getName().c_str());
  writer->String("num");
  writer->Uint(getNum());
  writer->String("row");
  writer->Uint(getRow());
  writer->String("col");
  writer->Uint(getCol());
  writer->String("state");
  writer->Uint(getState());
  writer->EndObject();
}
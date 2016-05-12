#include "button.h"

Button::Button()
{
  onOffState = 0;
}

Button::~Button()
{
}

void Button::startup(int _row, int _col, int _num, string _name)
{
  row = _row;
  col = _col;
  name = _name;
  num = _num;
  lastPressTime = 0;
  wasPressed = 0;
  overridden = false;
  // state = Button_ON;//default to on
  
  //cout << "creating Button " << row << ", " << col << ", " << name << ", " << num << endl;
}

bool Button::setState(int _newState)
{
  //returns true if state changed
  bool ret = false;
  if(overridden){
    return(ret);
  }
  if(onOffState != _newState){
    ret = true;
    wasPressed = true;
  }
  onOffState = _newState;
  return(ret);
}

void Button::serializeJson(Writer<StringBuffer>* writer)
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

void Button::setOverridden(bool _override)
{
  overridden = _override;
}

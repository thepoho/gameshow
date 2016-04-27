#ifndef _BUTTON_H
#define _BUTTON_H

#include "common_defines.h"

class Button
{
public:
  Button();
  ~Button();
  void startup(int _row, int _col, int _num, string _name);
  void setOverridden(bool _override);

  string getName() { return(name); }
  int getNum() { return(num); }
  int getRow() { return(row); }
  int getCol() { return(col); }
  int getState() { return(onOffState); }

  bool setState(int _newState);

  void serializeJson(Writer<StringBuffer>* writer);
private:
  int row, col, num;
  string name;
  int onOffState;
  bool overridden;
  
};

#endif //_BUTTON_H

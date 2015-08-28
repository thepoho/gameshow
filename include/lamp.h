#ifndef _LAMP_H
#define _LAMP_H

#include "common_defines.h"


class lamp
{
public:
	lamp();
	~lamp();
	void startup(int _row, int _col, int _num, string _name);

  string getName() { return(name); }

  void serializeJson(Writer<StringBuffer>* writer);

  bool setState(LampState _newState);

  LampState getState() { return(state); }
private:
  int row, col, num;
  string name;
  LampState state;  //use accessors?
};

#endif //_LAMP_H
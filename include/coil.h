#ifndef _COIL_H
#define _COIL_H

// #include <iostream>
#include <string>
// #include "game_show.h"
#include "common_defines.h"
// using namespace std;

class coil
{
public:
  coil();
  ~coil();
  void startup(int _num, string _name);

  int onOffState; //use accessors?
  string getName() { return(name); }
  bool getState() { return(state); }
  bool setState(bool _state);
  int getNumber() { return(num); }

  // unsigned int getLastOnTime(){  return(lastOnTime);  }
  // unsigned int getLastOffTime(){ return(lastOffTime); }
  
  // unsigned int getTurnOffTime(){ return(turnOffTime); }
  // void setTurnOffTime(unsigned int tot){ turnOffTime = tot; }

  // bool getShouldTurnOff(){ return(shouldTurnOff); }
  void setShouldTurnOff(unsigned int sso){ shouldTurnOff = sso; }

  bool update(unsigned int delta);

  void serializeJson(Writer<StringBuffer>* writer);
private:
  int num;
  string name;
  bool state;
  unsigned int onTimeRemaining, offTimeRemaining;
  bool shouldTurnOff;
  // coilController* coil_controller;
  
};

#endif //_COIL_H
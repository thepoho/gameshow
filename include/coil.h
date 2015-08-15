#ifndef _COIL_H
#define _COIL_H

#include <iostream>
#include <string>
using namespace std;

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
private:
  int num;
  string name;
  bool state;
  unsigned int lastOnTime, lastOffTime;
  
};

#endif //_COIL_H
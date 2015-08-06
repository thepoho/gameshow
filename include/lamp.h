#ifndef _LAMP_H
#define _LAMP_H

#include <iostream>
#include <string>
using namespace std;

enum LampState{ LAMP_ON, LAMP_OFF, LAMP_FLASH_FAST, LAMP_FLASH_SLOW };

class lamp
{
public:
	lamp();
	~lamp();
	void startup(int _row, int _col, int _num, string _name);

  LampState state;  //use accessors?
  string getName() { return(name); }
private:
	int row, col, num;
  string name;
};

#endif //_LAMP_H
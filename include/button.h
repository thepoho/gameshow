#ifndef _BUTTON_H
#define _BUTTON_H

#include <iostream>
#include <string>
using namespace std;

// enum SwitchState{ SWITCH_ON, SWITCH_OFF, SWITCH_FLASH_FAST, SWITCH_FLASH_SLOW };

class button
{
public:
	button();
	~button();
	void startup(int _row, int _col, int _num, string _name);

  // SwitchState state;  //use accessors?
private:
	int row, col, num;
  string name;
};

#endif //_BUTTON_H
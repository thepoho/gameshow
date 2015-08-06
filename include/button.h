#ifndef _BUTTON_H
#define _BUTTON_H

#include <iostream>
#include <string>
using namespace std;

class button
{
public:
	button();
	~button();
	void startup(int _row, int _col, int _num, string _name);

  int onOffState; //use accessors?
  string getName() { return(name); }
private:
	int row, col, num;
  string name;
  
};

#endif //_BUTTON_H
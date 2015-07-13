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

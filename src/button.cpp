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
  //cout << "creating button " << row << ", " << col << ", " << name << ", " << num << endl;
}

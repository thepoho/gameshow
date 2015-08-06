#include "coil.h"

coil::coil()
{
}

coil::~coil()
{
}

void coil::startup(int _num, string _name)
{
  name  = _name;
  num   = _num;
//  cout << "creating coil " << row << ", " << col << ", " << name << ", " << num << endl;
}

void coil::setState(bool _state){
  //Some checking here to ensure we are allowed to change states due to on-time and cooldown
}
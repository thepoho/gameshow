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
  shouldTurnOff = 1;
  turnOffTime = 0;
}

bool coil::setState(bool _state){
  if(state == _state){
    //state has not changed - nothing to do!
    return false;
  }else{
    //state has changed!
    state = _state;
    return true;
  }
}
#include "coil.h"
// #include "coil_controller.h"
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
  shouldTurnOff = TRUE;
  state = COIL_OFF;
  onTimeRemaining = offTimeRemaining = 0;
}

bool coil::setState(bool _state){
  if(state != _state){  //asking to go to a new state
    if(_state == COIL_ON){  //transitioning to an ON state
      if(offTimeRemaining == 0){ //cooldown complete!
        state = _state;
        onTimeRemaining = COIL_ON_TIME;
        return true;
      }
    }else{  //turning off
      state = _state;
      onTimeRemaining = 0;
      offTimeRemaining = COIL_COOLDOWN_TIME;
      return true;
    }
  }
  return false; //nothing changed here, boss
}

void coil::update(unsigned int delta)
{
  if(shouldTurnOff){
    if(state == COIL_ON){  //currently on
      if(onTimeRemaining > delta){ //more time remaining than the delta
        onTimeRemaining -= delta;
      }else{
        setState(COIL_OFF);  //this will also reset onTimeRemaining
      }
    }else{ //if our state is COIL_OFF
      if(offTimeRemaining > 0){
        if(offTimeRemaining > delta){
          offTimeRemaining -= delta;
        }else{
          offTimeRemaining = 0; //cooldown complete!
        }
      }
    }
  }
}

void coil::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String(name.c_str());
  writer->String("num");
  writer->Uint(num);
  // writer->String("row");
  // writer->Uint(row);
  // writer->String("col");
  // writer->Uint(col);
  writer->String("state");
  writer->Uint(state);
  writer->EndObject();
}
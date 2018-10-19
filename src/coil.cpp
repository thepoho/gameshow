#include "coil.h"
// #include "coil_controller.h"
Coil::Coil()
{
}

Coil::~Coil()
{
}

void Coil::startup(int _num, string _name, int _onTime, int _coolDownTime)
{
  name  = _name;
  num   = _num;
  shouldTurnOff = TRUE;
  state = COIL_OFF;
  onTimeRemaining = offTimeRemaining = 0;

  onTime = _onTime;
  coolDownTime = _coolDownTime;
  // cout << "Coil " << name << " starting up. ontime is " << onTime << endl;
}

bool Coil::setState(bool _state){
  if(state != _state){  //asking to go to a new state
    // cout << "new state for " << name << " is " << _state << endl;
    if(shouldTurnOff){
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
        // cout << "just turned off " << name << endl;
        return true;
      }
    }else{
      //a flipper or something that can stay on indefinitely so dont care about cooldown or Coil on times
      state = _state;
      return true;
    }
  }
  return false; //nothing changed here, boss
}

bool Coil::update(unsigned int delta)
{
  // if(strcmp(name, 'l_slingshot') == 0){
  //   cout << "lslingshot";
  // }
  bool ret = false;
  if(shouldTurnOff){
    if(state == COIL_ON){  //currently on
      if(onTimeRemaining > delta){ //more time remaining than the delta
        onTimeRemaining -= delta;
      }else{
        // cout << "trying to turn off " << name << endl;
        ret = setState(COIL_OFF);  //this will also reset onTimeRemaining
        // cout << "ret is now " << ret << endl;
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
  return(ret);
}

void Coil::serializeJson(Writer<StringBuffer>* writer)
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

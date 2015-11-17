#ifndef _STATE_BASIC_H
#define _STATE_BASIC_H

#include "common_defines.h"
#include "game_controller.h"
#include "state_core.h"

class StateBasic : public StateCore
{
public:
  StateBasic();
  ~StateBasic();
  void startup(GameController* _game_controller);

  void automaticCoils();
  void update(unsigned int delta);
  
private:

};

#endif //_STATE_BASIC_H
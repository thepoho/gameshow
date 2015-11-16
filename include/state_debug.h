#ifndef _STATE_DEBUG_H
#define _STATE_DEBUG_H

#include "common_defines.h"
#include "game_controller.h"
#include "state_core.h"
// #include "game_show.h"

class StateDebug: public StateCore
{
public:
  StateDebug();
  ~StateDebug();
  void startup(GameController* _game_controller);

  void automaticCoils();
  void update(unsigned int delta);


  void serializeJson(Writer<StringBuffer>* writer);
  
  void sendToWeb();
  
private:
  string name;

  GameController* pGameController;
  unsigned int elapsedTime;
};

#endif //_STATE_DEBUG_H
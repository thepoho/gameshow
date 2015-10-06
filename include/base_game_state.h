#ifndef _BASE_GAME_STATE_H
#define _BASE_GAME_STATE_H

#include "common_defines.h"
#include "game_controller.h"
// #include "game_show.h"

class BaseGameState
{
public:
  BaseGameState();
  ~BaseGameState();
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

#endif //_BASE_GAME_STATE_H
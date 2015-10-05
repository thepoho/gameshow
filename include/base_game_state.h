#ifndef _BASE_GAME_STATE_H
#define _BASE_GAME_STATE_H

#include "common_defines.h"
#include "game_show.h"

class BaseGameState
{
public:
  BaseGameState();
  ~BaseGameState();
  void startup(GameShow* _game_show);

  void automaticCoils();
  void update(unsigned int delta);
  
  
private:
  string name;

  GameShow* game_show;
  unsigned int elapsedTime;
};

#endif //_BASE_GAME_STATE_H
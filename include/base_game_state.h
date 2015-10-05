#ifndef _BASE_GAME_STATE_H
#define _BASE_GAME_STATE_H

#include "common_defines.h"
#include "game_show.h"

class baseGameState
{
public:
  baseGameState();
  ~baseGameState();
  void startup(GameShow* _game_show);

  void automaticCoils();
  void update();
  
  
private:
  string name;

  GameShow* game_show;

};

#endif //_BASE_GAME_STATE_H
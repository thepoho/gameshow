#ifndef _BASE_GAME_STATE_H
#define _BASE_GAME_STATE_H

#include "common_defines.h"

class baseGameState
{
public:
  baseGameState();
  ~baseGameState();
  void startup();
  
  
private:
  string name;
};

#endif //_BASE_GAME_STATE_H
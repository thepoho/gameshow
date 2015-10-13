#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include "common_defines.h"
#include "game_controller.h"
#include "base_game_state.h"

class GameShow
{
public:
  GameShow();
  ~GameShow();
  void run();

  void doAutoCoils();

  void processWebMessages();
  void setGameState(GameState _state);
  
private:
  GameState game_state;
  GameController* pGameController;
  BaseGameState*    pGameState;

  unsigned int lastTickTime;
};

#endif //_GAME_SHOW_H
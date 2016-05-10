#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include "common_defines.h"
#include "game_controller.h"

/// Game States ///
#include "state_core.h"
#include "state_basic.h"
#include "state_debug.h"

class GameShow
{
public:
  GameShow();
  ~GameShow();
  void run();
  void test();

  void doAutoCoils();

  void processWebMessages();
  void setGameState(string _state);
  
private:
  // GameState game_state;
  GameController* pGameController;
  StateCore*    pGameState;

  unsigned int lastTickTime;

  void doSetNewGameState(StateCore *_new_state);
};

#endif //_GAME_SHOW_H

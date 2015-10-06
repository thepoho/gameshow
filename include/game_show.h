#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

#include "common_defines.h"
#include "game_controller.h"
#include "base_game_state.h"

class GameShow
{
public:
  GameShow();
  ~GameShow();
  void run();

  // string getButtonInfoString();
  // string getLampInfoString();

  void doAutoCoils();

  void processWebMessages();

  void sendWebMessage(string message);

  void setGameState(GameState _state);
  void sendGameStateToWeb();

  // CoilController* getCoilController();
  
private:
  GameState game_state;
  GameController* pGameController;
  BaseGameState*    pGameState;
};

// #include "pin_io.h"
// #include "socket_server.h"
//#include "lamp_matrix_test.h"


#endif //_GAME_SHOW_H
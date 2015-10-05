#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

#include "common_defines.h"

class GameShow
{
public:
  GameShow();
  ~GameShow();
  void run();

  // string getButtonInfoString();
  // string getLampInfoString();

  void doAutoCoils();

  void processMessage(Document* document);

  void sendWebMessage(string message);

  void setGameState(GameState _state);
  void sendGameStateToWeb();
private:
  GameState game_state;
  // baseGameState* p_game_state;
};

#include "pin_io.h"
#include "lamp.h"
#include "lamp_controller.h"
#include "button.h"
#include "button_controller.h"
#include "coil.h"
#include "coil_controller.h"
#include "socket_server.h"
// #include "base_game_state.h"
//#include "lamp_matrix_test.h"




#endif //_GAME_SHOW_H

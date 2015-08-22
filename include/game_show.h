#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

#include "common_defines.h"

#include "mongoose.h"

#include "pin_io.h"
#include "lamp.h"
#include "lamp_controller.h"
#include "button.h"
#include "button_controller.h"
#include "coil.h"
#include "coil_controller.h"
#include "socket_server.h"
//#include "lamp_matrix_test.h"



class GameShow
{
public:
  GameShow();
  ~GameShow();
  void update();
private:

};

#endif //_GAME_SHOW_H

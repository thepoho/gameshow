#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

#define SIZEOF(n) ((int)(sizeof(n) / sizeof(n[0])))
#define pohoNULL (0)
#define FALSE (0)
#define TRUE  (1)

#define COIL_COUNT (14)
#define FLASHER_COUNT (8)



#include "pin_io.h"
#include "lamp_controller.h"
#include "lamp.h"
#include "button_controller.h"
#include "button.h"
#include "coil_controller.h"
#include "coil.h"
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

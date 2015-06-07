#ifndef _GAME_SHOW_H
#define _GAME_SHOW_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wiring_pi.h"
#include "lamp_controller.h"
#include "lamp.h"
//#include "lamp_matrix_test.h"

#define SIZEOF(n) (sizeof(n) / sizeof(n[0]))

//enum LampState{ LAMP_ON, LAMP_OFF, LAMP_FLASH_FAST, LAMP_FLASH_SLOW };

void lampMatrixTest();
void setupLamps();
void update();

#endif //_GAME_SHOW_H
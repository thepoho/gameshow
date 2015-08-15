#ifndef _SERIAL_IO_H
#define _SERIAL_IO_H

#include "game_show.h"

#define DATA_PIN 23
#define CLOCK_PIN 24
#define LATCH_PIN 25
#define NUM_OUTPUTS 16

#define LOW 0
#define HIGH 1

class serialIo
{
public:
  serialIo();
  ~serialIo();
  void startup(PinIO* _pinio);
  void update();
private:
  char currentState[NUM_OUTPUTS];
  char previousState[NUM_OUTPUTS];

  PinIO* pinIo;

  void flushData();
};

#endif //_SERIAL_IO_H

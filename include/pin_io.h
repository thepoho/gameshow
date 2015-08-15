#ifndef _PINIO_H
#define _PINIO_H

// #include "game_show.h"
// #include "serial_io.h"

#ifdef _RASPI
#include <wiringPi.h>
#else
#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#endif

class PinIO
{
public:
  PinIO();
  ~PinIO();
  void startup();
  void setPinMode(int pin, int mode);
  //void pullUpDnControl(int pin, int pud);
  void pinWrite(int pin, int value);
  //void pwmWrite(int pin, int value);
  int pinRead(int pin);  //needed
  void shiftOut(int data_pin, int clock_pin, int latch_pin, char* data);
  //int analogRead(int pin);
  //void analogWrite(int pin, int value);
  void doDelay(unsigned int howLong);
  unsigned int getMillis(void);
  //unsigned int tmp = 0;

  // serialIo* serial_io;
};

#endif

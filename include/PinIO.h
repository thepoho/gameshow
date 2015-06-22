#ifndef _PINIO_H
#define _PINO_H

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
  void pinMode(int pin, int mode);
  //void pullUpDnControl(int pin, int pud);
  void digitalWrite(int pin, int value);
  //void pwmWrite(int pin, int value);
  //int digitalRead(int pin);  //needed
  //int analogRead(int pin);
  //void analogWrite(int pin, int value);
  //void delay(a);
};

#endif
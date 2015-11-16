#ifndef _PINIO_H
#define _PINIO_H

// #include "game_show.h"
// #include "serial_io.h"

#ifdef GAMESHOW_BUILD_RASPI
  #include <wiringPi.h>
#else
  #define LOW 0
  #define HIGH 1
  #define INPUT 0
  #define OUTPUT 1
#endif

#define SERIAL_DATA_PIN 23
#define SERIAL_CLOCK_PIN 24
#define SERIAL_LATCH_PIN 25
#define SERIAL_NUM_OUTPUTS 24

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
  void shiftOut(char* data);
  //int analogRead(int pin);
  //void analogWrite(int pin, int value);
  void doDelay(unsigned int howLong);
  unsigned int getMillis(void);

  void flushSerialData();
  void setSerialOutput(int num, char state);

private:
  char currentSerialState[SERIAL_NUM_OUTPUTS];

  bool serialOutputsDirty;
};

#endif

#include "pin_io.h"
#include "game_show.h"
#include <stdio.h>
#include <stdlib.h>

PinIO::PinIO()
{

}
PinIO::~PinIO()
{

}

#ifdef _RASPI
void PinIO::startup()
{
  if (wiringPiSetup() == -1)
    exit(0);

  // serial_io.startup(*this);
}

void PinIO::setPinMode(int pin, int mode)
{
  pinMode(pin, mode);
}

void PinIO::pinWrite(int pin, int value)
{
  digitalWrite(pin, value);
}

int PinIO::pinRead(int pin)
{
  return(digitalRead(pin));
}

void PinIO::shiftOut(int data_pin, int clock_pin, int latch_pin, char* data)
{
  digitalWrite(latch_pin, LOW);
  
  digitalWrite(clock_pin, LOW);
  for (int i = 0; i < SIZEOF(data); i++){
    digitalWrite(data_pin, data[i]);
    digitalWrite(clock_pin, HIGH);
    digitalWrite(clock_pin, LOW);
  }
  digitalWrite(latch_pin, HIGH);
}

void PinIO::doDelay(unsigned int howLong)
{
  delay(howLong);
}

unsigned int PinIO::getMillis(void)
{
  return(millis());
}
#else
void PinIO::startup(){}
void PinIO::setPinMode(int pin, int mode){}
void PinIO::pinWrite(int pin, int value){}
int PinIO::pinRead(int pin){ return(0); }
void PinIO::doDelay(unsigned int howLong){}

unsigned int tmp = 0;
unsigned int PinIO::getMillis(void){ return(++tmp); }
#endif

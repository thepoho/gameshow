#include "pin_io.h"
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

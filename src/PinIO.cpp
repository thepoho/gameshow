#include "PinIO.h"

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

void PinIO::pinMode(int pin, int mode)
{
  pinMode(pin, mode);
}

void PinIO::digitalWrite(int pin, int value)
{
  digitalWrite(pin, value);
}

int PinIO::digitalRead(int pin)
{
  return(digitalRead(pin));
}

int PinIO::delay(unsigned int howLong)
{
  delay(howLong);
}

unsigned int PinIO::millis(void)
{
  millis();
}
#else
void PinIO::startup(){}
void PinIO::pinMode(int pin, int mode){}
void PinIO::digitalWrite(int pin, int value){}
int PinIO::digitalRead(int pin){ return(0); }
void PinIO::delay(unsigned int howLong){}

unsigned int tmp = 0;
unsigned int PinIO::millis(void){ return(++tmp); }
#endif
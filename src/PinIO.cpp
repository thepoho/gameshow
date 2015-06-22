#include "PinIO.h"

PinIO::PinIO()
{

}
PinIO::~PinIO()
{

}

void PinIO::startup()
{
#ifdef _RASPI
  if (wiringPiSetup() == -1)
    exit(0);
#else
  //nothing!
#endif
}

void PinIO::pinMode(int pin, int mode)
{
#ifdef _RASPI
  pinMode(pin, mode);
#else
  //nothing!
#endif
}

void PinIO::digitalWrite(int pin, int value)
{
#ifdef _RASPI
  digitalWrite(pin, value);
#else
  //nothing!
#endif
}
#include "serial_io.h"

int rowPins[8] = { 0, 2, 3, 12, 13, 14, 21, 22 };

serialIo::serialIo()
{

}

serialIo::~serialIo()
{

}

void serialIo::startup()
{

}

void serialIo::update()
{
  //check if currentState != previousState
}

void serialIo::flushData(){
  for (int i = 0; i < OUTPUTS; i++){

  }
}
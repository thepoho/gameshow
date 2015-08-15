#include "serial_io.h"

serialIo::serialIo()
{
  
}

serialIo::~serialIo()
{

}

void serialIo::startup(PinIO* _pinio)
{
  pinIo = _pinio;
}

void serialIo::update()
{
  //only flush data if something has changed!
  for (int i = 0; i < NUM_OUTPUTS; i++){
    if(currentState[i] != previousState[i]){
      flushData();
      break;
    }
  }
}

void serialIo::flushData()
{
  pinIo->shiftOut(DATA_PIN, CLOCK_PIN, LATCH_PIN, currentState);
}
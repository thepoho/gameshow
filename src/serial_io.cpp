#include "serial_io.h"

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
  //only flush data if something has changed!
  for (int i = 0; i < NUM_OUTPUTS; i++){
    if(currentState[i] != previousState[i]){
      flushData();
      break;
    }
  }
}

void serialIo::flushData(){
  digitalWrite(LATCH_PIN, LOW);
  
  digitalWrite(CLOCK_PIN, LOW);
  for (int i = 0; i < NUM_OUTPUTS; i++){
    digitalWrite(DATA_PIN, currentState[i]);
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
  digitalWrite(LATCH_PIN, HIGH);
}
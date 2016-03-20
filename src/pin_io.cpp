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

#ifdef GAMESHOW_BUILD_RASPI
#include <wiringPi.h>
void PinIO::startup()
{
  if (wiringPiSetup() == -1)
    exit(0);

  serialOutputsDirty = TRUE;
  setPinMode(SERIAL_CLOCK_PIN, OUTPUT);
  setPinMode(SERIAL_LATCH_PIN, OUTPUT);
  setPinMode(SERIAL_DATA_PIN, OUTPUT);
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

void PinIO::flushSerialData()
{
  if(serialOutputsDirty){
    cout << "Flushing serial data: ";
    digitalWrite(SERIAL_LATCH_PIN, LOW);
    
    digitalWrite(SERIAL_CLOCK_PIN, LOW);
    // for (int i = 0; i < SIZEOF(currentSerialState); i++){
    for (int i = SIZEOF(currentSerialState)-1; i >= 0; i--){
      cout << currentSerialState[i];
      digitalWrite(SERIAL_DATA_PIN, currentSerialState[i]);
      digitalWrite(SERIAL_CLOCK_PIN, HIGH);
      digitalWrite(SERIAL_CLOCK_PIN, LOW);
    }
    cout << endl;
    cout << "SERIAL LATCH IS " << SERIAL_LATCH_PIN << endl;
    digitalWrite(SERIAL_LATCH_PIN, HIGH);
    serialOutputsDirty = FALSE;
  }
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
int  PinIO::pinRead(int pin){ return(0); }
void PinIO::doDelay(unsigned int howLong){ usleep(howLong * 1000);}
void PinIO::flushSerialData(){
  if(serialOutputsDirty){
    cout << "Flushing serial data: ";
    for (int i = SIZEOF(currentSerialState)-1; i >= 0; i--){
      cout << currentSerialState[i];
    }
    cout << endl;
    serialOutputsDirty = FALSE;
  }
}

unsigned int tmp = 0;
unsigned int PinIO::getMillis(void){ return(++tmp); }
#endif

void PinIO::setSerialOutput(int num, bool state)
{
  currentSerialState[num] = state;
  serialOutputsDirty = TRUE;
}

#ifndef _SERIAL_IO_H
#define _SERIAL_IO_H

#define DATA_PIN 23
#define CLOCK_PIN 24
#define LATCH_PIN 25
#define OUTPUTS 16
class serialIo
{
public:
  serialIo();
  ~serialIo();
  void startup();
  void update();
private:
  char currentState[OUTPUTS];
  char previousState[OUTPUTS];

  void flushData();
};

#endif //_SERIAL_IO_H
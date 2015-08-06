#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "coil.h"
#include "game_show.h"

#define COIL_MAX_ON_TIME 500
#define COIL_COOLDOWN_TIME 200

class coilController
{
public:
  coilController();
  ~coilController();

  void update(unsigned int delta);

  void startup(PinIO* _pinio);
  void setCoilState(string name, bool state);
  coil *getCoil(string name);
private:
  PinIO* pinIo;

  coil coils[16];
  void flushCoils();
  unsigned int elapsedTime = 0;
};

#endif

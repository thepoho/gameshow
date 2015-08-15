#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "game_show.h"
#include "coil.h"

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

  coil coils[COIL_COUNT];
  unsigned int elapsedTime;
};

#endif

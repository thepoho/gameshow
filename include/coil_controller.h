#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "coil.h"
#include "game_show.h"

#define COIL_MAX_ON_TIME 500
#define COIL_COOLDOWN_TIME 200
#define COIL_ON_TIME 150 //the amount of time a coil is generally fired for
#define COIL_OFF 0
#define COIL_ON  1

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

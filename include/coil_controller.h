#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "coil.h"
#include "game_show.h"  

class coilController
{
public:
  coilController();
  ~coilController();

  void update(unsigned int delta);

  void startup(GameShow* _game_show, PinIO* _pinio);
  void setCoilState(string name, bool state);
  coil *getCoil(string name);
private:
  PinIO* pinIo;
  GameShow* game_show;

  coil coils[COIL_COUNT];
  unsigned int elapsedTime;
};

#endif

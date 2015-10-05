#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "coil.h"
#include "game_show.h"

class CoilController
{
public:
  CoilController();
  ~CoilController();

  void update(unsigned int delta);

  void startup(GameShow* _game_show, PinIO* _pinio);
  void setCoilState(string name, bool state);
  Coil *getCoil(string name);
  string getInfoString();
  void updateWebCoilState(Coil _coil);
private:
  PinIO* pinIo;
  GameShow* game_show;

  Coil coils[COIL_COUNT];
  unsigned int elapsedTime;
};

#endif

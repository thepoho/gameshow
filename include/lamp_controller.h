#ifndef _LAMP_CONTROLLER_H
#define _LAMP_CONTROLLER_H

#include "lamp.h"
#include "game_show.h"

#define SLOW_FLASH_DELAY 1600
#define FAST_FLASH_DELAY 400


class lampController
{
public:
  lampController();
  ~lampController();

  void update(unsigned int delta);

  void startup(GameShow* _game_show, PinIO* _pinio);
  void setLampState(string name, LampState state);
  lamp *getLamp(string name);

  void updateWebLampState(lamp* _lmp);

  string getInfoString();

private:
  PinIO* pinIo;
  GameShow* game_show;

  lamp lamps[8][8];
  void flushLamps();
  unsigned int elapsedTime;
  unsigned int lastFastFlash;
  bool fastFlashStatus;
  unsigned int lastSlowFlash;
  bool slowFlashStatus;
};

#endif

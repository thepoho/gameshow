#ifndef _LAMP_CONTROLLER_H
#define _LAMP_CONTROLLER_H

#include "lamp.h"
#include "socket_server.h"
#include "pin_io.h"
// #include "game_show.h"

#define SLOW_FLASH_DELAY 1600
#define FAST_FLASH_DELAY 400


class LampController
{
public:
  LampController();
  ~LampController();

  void update(unsigned int delta);

  void startup(PinIO* _pinio, SocketServer* _socket_server);
  void setLampState(string name, LampState state);
  Lamp *getLamp(string name);

  void updateWebLampState(Lamp* _lmp);

  string getInfoString();

private:
  PinIO* pPinIo;
  // GameShow* game_show;
  SocketServer* pSocketServer;

  Lamp lamps[8][8];
  void flushLamps();
  unsigned int elapsedTime;
  unsigned int lastFastFlash;
  bool fastFlashStatus;
  unsigned int lastSlowFlash;
  bool slowFlashStatus;
};

#endif

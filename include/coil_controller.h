#ifndef _COIL_CONTROLLER_H
#define _COIL_CONTROLLER_H

#include "coil.h"
#include "socket_server.h"
#include "pin_io.h"
// #include "game_show.h"

class CoilController
{
public:
  CoilController();
  ~CoilController();

  void update(unsigned int delta);

  void startup(PinIO* _pinio, SocketServer* _socket_server);
  void setCoilState(string name, bool state);
  Coil *getCoil(string name);
  string getInfoString();
  void updateWebCoilState(Coil _coil);
  void setAllState(bool state);
  void fireCoil(string name);
private:
  PinIO* pPinIo;
  // GameShow* game_show;
  SocketServer* pSocketServer;
  void loadCoilsFromFile();

  Coil *coils;
  unsigned int elapsedTime;
  bool allState;
};

#endif

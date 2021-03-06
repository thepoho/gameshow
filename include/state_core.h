#ifndef _STATE_CORE_H
#define _STATE_CORE_H

#include "common_defines.h"
#include "game_controller.h"
// #include "game_show.h"

class StateCore
{
public:
  StateCore();
  ~StateCore();
  void startup(GameController* _game_controller);

  void automaticCoils();
  void update(unsigned int delta);

  void serializeJson(Writer<StringBuffer>* writer);

  void sendToWeb();

  void sendAllStatesToWeb();

  string getName() {return name;}

protected:
  string name;

  GameController* pGameController;
  unsigned int elapsedTime;

  void setCoilState(string name, bool state);
  void fireCoil(string name);
  void fireCoilDelay(string name, unsigned int delay);
  void resetAllWasPressedReleased();
  void afterUpdate(unsigned int delta);
  void checkForShutdown();
  bool getButtonState(string name);
};

#endif //_STATE_CORE_H

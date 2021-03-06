#ifndef _BUTTON_CONTROLLER_H
#define _BUTTON_CONTROLLER_H

#include "button.h"
// #include "game_show.h"
#include "socket_server.h"
#include "pin_io.h"

#include <sstream>


class ButtonController
{
public:
  ButtonController();
  ~ButtonController();

  void update(unsigned int delta);

  void startup(PinIO* _pinio, SocketServer* _socket_server);
  bool getButtonState(string name);
  Button *getButton(string name);
  void outputButtons();
  void setButtonState(Button *btn, bool newState);
  void setButtonStateByName(string name, bool newState);
  void overrideButtonState(string name, bool newState);
  void resetAllWasPressedReleased();

  string getInfoString();
private:
  PinIO* pPinIo;
  // GameShow* game_show;
  SocketServer* pSocketServer;

  void updateWebButtonState(Button *_btn);
  bool canUpdateButton(Button *btn);
  void loadButtonsFromFile();

  unsigned int elapsedTime;

  //static const int rowPins[8];
  //static const int colPins[3];  //8 columns, on a binary decoder

  //settings for column pins to set various columns.
  //probably should generate them at startup... but meh, hardcoding works
  //static const int colOutputs[8][3];

  Button buttons[8][8];
  // button buttons64[64];
};

#endif

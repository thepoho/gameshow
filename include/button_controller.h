#ifndef _BUTTON_CONTROLLER_H
#define _BUTTON_CONTROLLER_H

#include "button.h"
#include "game_show.h"

#include <sstream>


class buttonController
{
public:
  buttonController();
  ~buttonController();

  void update(unsigned int delta);

  void startup(GameShow* _game_show, PinIO* _pinio);
  bool getButtonState(string name);
  button *getButton(string name);
  void outputButtons();

  string getInfoString();
private:
  PinIO* pinIo;
  GameShow* game_show;

  void updateWebButtonState(button _btn);

  unsigned int elapsedTime;

  //static const int rowPins[8];
  //static const int colPins[3];  //8 columns, on a binary decoder

  //settings for column pins to set various columns.
  //probably should generate them at startup... but meh, hardcoding works
  //static const int colOutputs[8][3];

  button buttons[8][8];
  // button buttons[64];
};

#endif

#ifndef _BUTTON_CONTROLLER_H
#define _BUTTON_CONTROLLER_H

#include "button.h"
#include "game_show.h"



class buttonController
{
public:
  buttonController();
  ~buttonController();

  void update(int delta);

  void startup(PinIO* _pinio);
  bool getButtonState(string name);
  button *getButton(string name);
private:
  PinIO* pinIo;
  //static const int rowPins[8];
  //static const int colPins[3];  //8 columns, on a binary decoder

  //settings for column pins to set various columns.
  //probably should generate them at startup... but meh, hardcoding works
  //static const int colOutputs[8][3];

  button buttons[8][8];
};

#endif

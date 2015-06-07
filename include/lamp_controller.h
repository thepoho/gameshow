#ifndef _LAMP_CONTROLLER_H
#define _LAMP_CONTROLLER_H

#include "lamp.h"
#include "game_show.h"
class lampController
{
public:
  lampController();
  ~lampController();

  void update(int delta);

  void startup();
private:
  static const int rowPins[8];
  static const int colPins[3];  //8 columns, on a binary decoder

  //settings for column pins to set various columns.
  //probably should generate them at startup... but meh, hardcoding works
  static const int colOutputs[8][3];

  lamp lamps[8][8];
};

#endif
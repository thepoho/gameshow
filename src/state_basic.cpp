#include "state_basic.h"


StateBasic::StateBasic()
{

}

StateBasic::~StateBasic()
{
}

void StateBasic::startup(GameController* _game_controller)
{
  pGameController = _game_controller;
  name = "basic";
}


void StateBasic::update(unsigned int delta)
{
  StateCore::update(delta);
  automaticCoils();
  StateCore::afterUpdate(delta);
}

void StateBasic::automaticCoils()
{

  ///// Right Flipper
  if (getButtonState("right_flipper")){
    setCoilState("right_flipper", COIL_ON);
  }
  else{
    setCoilState("right_flipper", COIL_OFF);
  }

  ///// Left Flipper
  if (getButtonState("left_flipper")){
    setCoilState("left_flipper", COIL_ON);
  }
  else{
    setCoilState("left_flipper", COIL_OFF);
  }

  ///// Jets
  if (getButtonState("left_jet")){
    fireCoil("left_jet");
  }
  if (getButtonState("right_jet")){
    fireCoil("right_jet");
  }
  if (getButtonState("bottom_jet")){
    fireCoil("bottom_jet");
  }

  ///// Slingshots
  if (getButtonState("left_slingshot")){
    fireCoil("left_slingshot");
  }
  if (getButtonState("right_slingshot")){
    fireCoil("right_slingshot");
  }

  ///// Outhole
  if (getButtonState("outhole")){
    //fireCoilDelay("outhole_kicker", 2000);
    fireCoil("outhole_kicker");
  }
  if (getButtonState("credit_button")){
    fireCoil("ball_shooter_lane_feeder");
  }

  if (getButtonState("ball_popper")){
    fireCoil("ball_popper");
  }
}

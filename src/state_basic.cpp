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
  elapsedTime += delta;
  automaticCoils();
}

void StateBasic::automaticCoils()
{

  ///// Right Flipper

  if (pGameController->buttonController()->getButtonState("right_flipper")){
    pGameController->coilController()->setCoilState("right_flipper", COIL_ON);
  }
  else{
    pGameController->coilController()->setCoilState("right_flipper", COIL_OFF);
  }

  ///// Left Flipper

  if (pGameController->buttonController()->getButtonState("left_flipper")){
    pGameController->coilController()->setCoilState("left_flipper", COIL_ON);
  }
  else{
    pGameController->coilController()->setCoilState("left_flipper", COIL_OFF);
  }

  ///// Jets

  if (pGameController->buttonController()->getButtonState("left_jet")){
    pGameController->coilController()->setCoilState("left_jet", COIL_ON);
  }
  if (pGameController->buttonController()->getButtonState("right_jet")){
    pGameController->coilController()->setCoilState("right_jet", COIL_ON);
  }
  if (pGameController->buttonController()->getButtonState("bottom_jet")){
    pGameController->coilController()->setCoilState("bottom_jet", COIL_ON);
  }
  if (pGameController->buttonController()->getButtonState("left_slingshot")){
    pGameController->coilController()->setCoilState("left_slingshot", COIL_ON);
  }
  if (pGameController->buttonController()->getButtonState("right_slingshot")){
    pGameController->coilController()->setCoilState("right_slingshot", COIL_ON);
  }
}
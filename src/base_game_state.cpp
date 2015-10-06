#include "base_game_state.h"


BaseGameState::BaseGameState()
{

}

BaseGameState::~BaseGameState()
{
}

void BaseGameState::startup(GameController* _game_controller)
{
  pGameController = _game_controller;
  name = "base";
}

void BaseGameState::update(unsigned int delta)
{
  automaticCoils();
  elapsedTime += delta;
}

void BaseGameState::automaticCoils()
{

  if (pGameController->buttonController()->getButtonState("right_flipper")){
    pGameController->coilController()->setCoilState("right_flipper", COIL_ON);
    // lamp_controller.setLampState("truck_t", LAMP_ON);
  }
  else{
    pGameController->coilController()->setCoilState("right_flipper", COIL_OFF);
    // lamp_controller.setLampState("truck_t", LAMP_OFF);
  }

  if (pGameController->buttonController()->getButtonState("left_flipper")){
    pGameController->coilController()->setCoilState("left_flipper", COIL_ON);
    // lamp_controller.setLampState("truck_r", LAMP_ON);
  }
  else{
    pGameController->coilController()->setCoilState("left_flipper", COIL_OFF);
    // lamp_controller.setLampState("truck_r", LAMP_OFF);
  }

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
#include "base_game_state.h"


BaseGameState::BaseGameState()
{

}

BaseGameState::~BaseGameState()
{
}

void BaseGameState::startup(GameShow* _game_show)
{
  game_show = _game_show;
  name = "base";
}

void BaseGameState::update(unsigned int delta)
{
  automaticCoils();
  elapsedTime += delta;
}

void BaseGameState::automaticCoils()
{
  // game_show::button_controller;

  // if (button_controller.getButtonState("right_flipper")){
  //   coil_controller.setCoilState("right_flipper", COIL_ON);
  //   // lamp_controller.setLampState("truck_t", LAMP_ON);
  // }
  // else{
  //   coil_controller.setCoilState("right_flipper", COIL_OFF);
  //   // lamp_controller.setLampState("truck_t", LAMP_OFF);
  // }

  // if (button_controller.getButtonState("left_flipper")){
  //   coil_controller.setCoilState("left_flipper", COIL_ON);
  //   // lamp_controller.setLampState("truck_r", LAMP_ON);
  // }
  // else{
  //   coil_controller.setCoilState("left_flipper", COIL_OFF);
  //   // lamp_controller.setLampState("truck_r", LAMP_OFF);
  // }

  // if (button_controller.getButtonState("left_jet")){
  //   coil_controller.setCoilState("left_jet", COIL_ON);
  // }
  // if (button_controller.getButtonState("right_jet")){
  //   coil_controller.setCoilState("right_jet", COIL_ON);
  // }
  // if (button_controller.getButtonState("bottom_jet")){
  //   coil_controller.setCoilState("bottom_jet", COIL_ON);
  // }
  // if (button_controller.getButtonState("left_slingshot")){
  //   coil_controller.setCoilState("left_slingshot", COIL_ON);
  // }
  // if (button_controller.getButtonState("right_slingshot")){
  //   coil_controller.setCoilState("right_slingshot", COIL_ON);
  // }
}
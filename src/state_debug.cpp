#include "state_debug.h"

StateDebug::StateDebug()
{

}

StateDebug::~StateDebug()
{
}

void StateDebug::startup(GameController* _game_controller)
{
  pGameController = _game_controller;
  name = "debug";
  // cout << "State Debug starting up!" << endl;
}


void StateDebug::update(unsigned int delta)
{
  // automaticCoils();
  elapsedTime += delta;
  // cout << "DEBUG UPDATE" << endl;
  
}
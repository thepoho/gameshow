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
}


void StateDebug::update(unsigned int delta)
{
  // automaticCoils();
  elapsedTime += delta;
}

void StateDebug::automaticCoils()
{

}

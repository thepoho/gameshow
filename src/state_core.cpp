#include "state_core.h"


StateCore::StateCore()
{

}

StateCore::~StateCore()
{
}

void StateCore::startup(GameController* _game_controller)
{
  pGameController = _game_controller;
  name = "core";
  // cout << "State core starting up" << endl;
}


void StateCore::update(unsigned int delta)
{
  //Usually expect this to be overridden. Make it virtual? Still need to ensure time is updated
  elapsedTime += delta;
}

void StateCore::afterUpdate(unsigned int delta){
  checkForShutdown();
  resetAllWasPressedReleased();
}


void StateCore::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String("game_state");
  writer->String("data");

  writer->StartObject();
  writer->String("value");
  writer->String(name.c_str());
  writer->EndObject();

  writer->EndObject();
}

void StateCore::sendToWeb()
{
  StringBuffer s;
  Writer<StringBuffer> writer(s);

  serializeJson(&writer);

  pGameController->socketServer()->enqueueMessage(s.GetString());
}

void StateCore::sendAllStatesToWeb()
{
  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("game_states");
  writer.String("data");
  writer.StartArray();
  writer.String("debug");
  writer.String("basic");
  writer.EndArray();
  writer.EndObject();

  pGameController->socketServer()->enqueueMessage(s.GetString());
}

void StateCore::setCoilState(string name, bool state)
{
  //handy accessor method
  pGameController->coilController()->setCoilState(name, state);
}

void StateCore::fireCoil(string name)
{
  //handy accessor method
  pGameController->coilController()->fireCoil(name);
}

bool StateCore::getButtonState(string name)
{
  //handy accessor method
  return(pGameController->buttonController()->getButtonState(name));
}

void StateCore::fireCoilDelay(string name, unsigned int delay)
{
  pGameController->delayedEventController()->createEvent("fire_coil", (elapsedTime + delay), name);
}

void StateCore::resetAllWasPressedReleased(){
  pGameController->buttonController()->resetAllWasPressedReleased();
}

void StateCore::checkForShutdown(){
  if(getButtonState("credit_button")){
    Button *pLeftFlipperButton = pGameController->buttonController()->getButton("left_flipper");
    if(pLeftFlipperButton->getWasPressed()){
      pGameController->lampController()->setLampState("all", LAMP_FLASH_FAST);
      cout << "TIME TO SHUT DOWN BABY!";
      system("shutdown -h now");
    }
  }
}

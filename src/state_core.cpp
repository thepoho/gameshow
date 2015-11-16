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
}


void StateCore::update(unsigned int delta)
{
  //Usually expect this to be overridden. Make it virtual? Still need to ensure time is updated
  elapsedTime += delta;
}


void StateCore::serializeJson(Writer<StringBuffer>* writer){
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

void StateCore::sendToWeb(){
  StringBuffer s;
  Writer<StringBuffer> writer(s);

  serializeJson(&writer);

  pGameController->socketServer()->enqueueMessage(s.GetString());
}
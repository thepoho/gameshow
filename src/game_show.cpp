#include "game_show.h"

  lampController    lamp_controller;
  buttonController  button_controller;
  coilController    coil_controller;
  socketServer      socket_server;
  PinIO *pPinIo;
  unsigned int lastTickTime;
  
GameShow::GameShow()
{

  pPinIo = new PinIO();
  
  pPinIo->startup();

  lamp_controller.startup(this, pPinIo);
  button_controller.startup(this, pPinIo);
  coil_controller.startup(this, pPinIo);

  // printf("not starting socket server yet!");
  // printf("this pointer is %p\n", this);
  socket_server.startup(this);


  // coil_controller.getCoil("trough")->setState(1);
  printf("setup complete\n");

}

GameShow::~GameShow()
{

}

void GameShow::run(){
  printf("starting main loop\n");
  while(1){
    
  //work out deltas
    unsigned int millis = pPinIo->getMillis();
    unsigned int delta = millis - lastTickTime;
    lastTickTime = millis;

    lamp_controller.update(delta);
    button_controller.update(delta);
    coil_controller.update(delta);

    // if (button_controller.getButtonState("trough_1_right")){
    //   lamp_controller.setLampState("truck_t", LAMP_ON);
    // }
    // else{
    //   lamp_controller.setLampState("truck_t", LAMP_OFF);
    // }

    // if (button_controller.getButtonState("tv_t")){
    //   lamp_controller.setLampState("trip_t", LAMP_ON);
    // }
    // else{
    //   lamp_controller.setLampState("trip_t", LAMP_OFF);
    // }
  }
}

void GameShow::sendWebMessage(string message)
{
  socket_server.enqueueMessage(message);
}

void GameShow::processMessage(Document* document){
  string message = document->FindMember("message")->value.GetString();
  
  if(message.compare("get_buttons") == 0){
    sendWebMessage(button_controller.getInfoString());
  
  }else if(message.compare("get_lamps") == 0){
    sendWebMessage(lamp_controller.getInfoString());
  
  }else if(message.compare("get_coils") == 0){
    sendWebMessage(coil_controller.getInfoString());
  
  }else if(message.compare("set_lamp_state") == 0){
    string name = document->FindMember("name")->value.GetString();
    LampState state = (LampState)document->FindMember("value")->value.GetInt();
    lamp_controller.setLampState(name, state);
  
  }else if(message.compare("set_coil_state") == 0){
    string name = document->FindMember("name")->value.GetString();
    int state = document->FindMember("value")->value.GetInt();
    coil_controller.setCoilState(name, state);
  }


}
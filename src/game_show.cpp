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
  printf("this pointer is %p\n", this);
  socket_server.startup(this);


  // coil_controller.getCoil("trough")->setState(1);
  printf("setup complete\n");
  printf("starting main loop\n");
  while (1){
    update();
  }
}

GameShow::~GameShow()
{

}

void GameShow::update(){
  //work out deltas
  unsigned int millis = pPinIo->getMillis();
  unsigned int delta = millis - lastTickTime;
  lastTickTime = millis;
  
 // printf("millis is %d\n", millis);
  // printf("millis is %d\n", millis);
  // if(millis % 400000 == 0){
  //   printf("zero\n");
  //   sendWebMessage("poho");
  // }

  lamp_controller.update(delta);
  button_controller.update(delta);
  coil_controller.update(delta);

  if (button_controller.getButtonState("trough_1_right")){
    lamp_controller.setLampState("truck_t", LAMP_ON);
  }
  else{
    lamp_controller.setLampState("truck_t", LAMP_OFF);
  }

  if (button_controller.getButtonState("tv_t")){
    lamp_controller.setLampState("trip_t", LAMP_ON);
  }
  else{
    lamp_controller.setLampState("trip_t", LAMP_OFF);
  }
}

string GameShow::getButtonInfoString(){
  return button_controller.getInfoString();
}

void GameShow::sendWebMessage(string message)
{
  // printf("sending ws message: %s\n", message);
  cout << "sending ws message: " << message << endl;
  socket_server.sendMessage(message);
}
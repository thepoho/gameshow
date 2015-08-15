#include "game_show.h"

  lampController    lamp_controller;
  buttonController  button_controller;
  coilController    coil_controller;
  serialIo          serial_io;
  PinIO *pPinIo;
  unsigned int lastTickTime;
  
GameShow::GameShow()
{

  pPinIo = new PinIO();
  
  pPinIo->startup();

  lamp_controller.startup(pPinIo);
  button_controller.startup(pPinIo);
  coil_controller.startup(pPinIo);
  serial_io.startup(pPinIo);
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
  
//  printf("millis is %d\n", millis);
 // printf("delta is %d\n", delta);
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
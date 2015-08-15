#include "coil_controller.h"

coilController::coilController()
{
  elapsedTime = 0;
}

coilController::~coilController()
{
}

void coilController::startup(PinIO* _pinio)
{
  pinIo = _pinio;
  //create all my coils
  string coilNames[COIL_COUNT] = {"r_flipper","l_flipper","l_slingshot","r_slingshot","ball_launcher",
                    "trough","f_bumper","l_bumper","r_bumper","r_popper","drop_target","l_gate","l_launch","bell"};
                    
  for(int i = 0; i < SIZEOF(coils); i++){
    coils[i].startup(i, coilNames[i]);
  }
}

void coilController::update(unsigned int delta)
{
  elapsedTime += delta;
  
  //See if any coils have been on for too long and turn them off
  
}


coil *coilController::getCoil(string name){
  for(int i = 0; i < SIZEOF(coils); i++){
    if(coils[i].getName() == name){
      return(&coils[i]);
    }
  }
  return(NULL);
}

void coilController::setCoilState(string name, bool state){
  coil *tmpCoil = getCoil(name);
  if (NULL != tmpCoil){
    if(tmpCoil->setState(state)){
      //will return true if state changed
      pinIo->setSerialOutput(tmpCoil->getNumber(), tmpCoil->getState());
    }
  }
}

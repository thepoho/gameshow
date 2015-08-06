#include "game_show.h"

lampController lamp_controller;
buttonController button_controller;
coilController coil_controller;


PinIO *pPinIo;

int main(void)
{
  pPinIo = new PinIO();
  
  pPinIo->startup();

  lamp_controller.startup(pPinIo);
  button_controller.startup(pPinIo);
  coil_controller.startup(pPinIo);
  printf("setup complete\n");
  printf("starting main loop\n");
  while (1){
    update();
  }
}

unsigned int lastTickTime;
void update(){
  //work out deltas
  unsigned int millis = pPinIo->getMillis();
  unsigned int delta = millis - lastTickTime;
  lastTickTime = millis;
  
//  printf("millis is %d\n", millis);
 // printf("delta is %d\n", delta);
  lamp_controller.update(delta);
  button_controller.update(delta);
  coil_controller.update(delta);
  
  //bool state = button_controller.getButtonState("left_flipper");
  //printf("left flipper is %d  ", state);

  //state = button_controller.getButtonState("truck_t");
  //printf("truck t is %d\n", state);

  //button_controller.outputButtons();

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
//void lampMatrixTest(){
//	if (wiringPiSetup() == -1)
//		return ;
//
//
//	int rowPins[8] = { 0, 2, 3, 12, 13, 14, 21, 22 };
//	int colPins[3] = { 8, 9, 7 };
//
//	int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
//
//	for (int i = 0; i < SIZEOF(rowPins); i++){
//		pinMode(rowPins[i], OUTPUT);
//		digitalWrite(rowPins[i], LOW);
//	}
//	for (int i = 0; i < SIZEOF(colPins); i++){
//		pinMode(colPins[i], OUTPUT);
//		digitalWrite(colPins[i], LOW);
//	}
//
//
//	while (1){
//		for (int k = 0; k <= 7; k++)
//		{
//			for (int i = 0; i < 3; i++){
//				digitalWrite(colPins[i], colOutputs[k][i]);
//			}
//
//			for (int i = 0; i < SIZEOF(rowPins); i++){ //TODO: change this to 8 - might be faster!
//				digitalWrite(rowPins[i], HIGH);
//			}
//
//			delay(15.0f);
//		}
//	}
//
//}

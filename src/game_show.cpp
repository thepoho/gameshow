#include "game_show.h"

lampController lamp_controller;
buttonController button_controller;

PinIO pinIo;

int main(void)
{
//	lampMatrixTest();
//  exit(0);

  pinIo.startup();

  lamp_controller.startup(&pinIo);
  button_controller.startup(&pinIo);
  //button_controller.startup();
  printf("setup complete\n");
  //sleep(1000);
  printf("starting main loop\n");
  while (1){
    update();
    //sleep(1);
   //printf("poho");
  }
//	lampMatrixTest();
  exit(0);
}

unsigned int lastTickTime;
void update(){
  //work out deltas
  unsigned int millis = pinIo.millis();
  unsigned int delta = millis - lastTickTime;
  lastTickTime = millis;
  
  lamp_controller.update(delta);
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

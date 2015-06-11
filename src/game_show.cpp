#include "game_show.h"

lampController lamp_controller;
buttonController button_controller;

int main(void)
{
  lamp_controller.startup();
  button_controller.startup();
  while (true){
    update();
  }
	//lampMatrixTest();
}

void update(){
  //work out deltas
  
  lamp_controller.update(0); //using delta 0 for now
}
void lampMatrixTest(){
	if (wiringPiSetup() == -1)
		return ;


	int rowPins[8] = { 0, 2, 3, 12, 13, 14, 21, 22 };
	int colPins[3] = { 8, 9, 7 };

	int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };

	for (int i = 0; i < SIZEOF(rowPins); i++){
		pinMode(rowPins[i], OUTPUT);
		digitalWrite(rowPins[i], LOW);
	}
	for (int i = 0; i < SIZEOF(colPins); i++){
		pinMode(colPins[i], OUTPUT);
		digitalWrite(colPins[i], LOW);
	}


	while (1){
		for (int k = 0; k <= 7; k++)
		{
			for (int i = 0; i < 3; i++){
				digitalWrite(colPins[i], colOutputs[k][i]);
			}

			for (int i = 0; i < SIZEOF(rowPins); i++){ //TODO: change this to 8 - might be faster!
				digitalWrite(rowPins[i], HIGH);
			}

			delay(15.0f);
		}
	}

}
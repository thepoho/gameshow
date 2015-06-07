#include "lamp_controller.h"

const int rowPins[8] = { 0, 2, 3, 12, 13, 14, 21, 22 };
const int colPins[3] = { 8, 9, 7 };
const int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
lampController::lampController()
{
}

lampController::~lampController()
{
}

void lampController::startup()
{
  for (int c = 0; c < 8; c++){
    for (int r = 0; r < 8; r++){
      lamps[c][r].startup(c, r);
    }
  }

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
  for (int i = 0; i < SIZEOF(colPins); i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void lampController::update(int delta)
{
  //TODO: update the lamp flash states based on deltas
  std::cout << "update";
  delay(1);

  for (int c = 0; c < 8; c++){ //columns
    
    //turn all rows off. Mabe unnecessary?
    //for(int i = 0; i < SIZEOF(rowPins); i++){
      //digitalWrite(rowPins[i], LOW);
    //}

    //set the appropriate output pins for the current column
    for (int i = 0; i < 3; i++){
      digitalWrite(colPins[i], colOutputs[k][i]);
    }

    for (int r = 0; r < 8; r++){
      //now for each row!
      lamp tmpLamp = lamps[c][r];
      if (tmpLamp.state == LAMP_ON){
        digitalWrite(rowPins[r], HIGH);
      }
      else{
        digitalWrite(rowPins[r], LOW);
      }
    }
  }
}
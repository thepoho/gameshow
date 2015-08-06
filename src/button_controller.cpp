#include "button_controller.h"


static const int rowPins[8] = { 4, 5, 6, 10, 11, 26, 27, 28 };
static const int colPins[3] = { 15, 16, 1 };
static const int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
const string buttonNames[8][8] = {
  { "plum_bob_tilt", "not", "top_lane_left", "easy_spin", "truck_t", "spin_wheel", "not_used", "right_flipper" },
  { "not_used", "outhole", "top_lane_middle", "center_ramp", "truck_r", "right_spinner", "not_used", "left_flipper" },
  { "credit_button", "trough_1_right", "top_lane_right", "tv_t", "truck_u", "spot_letter", "not_used", "not_used" },
  { "right_coin", "trough_2_left", "right_ramp", "tv_v", "truck_c", "not_used", "not_used", "left_jet" },
  { "center_coin", "not_used", "ball_popper", "trip_t", "truck_k", "left_outlane", "not_used", "right_jet" },
  { "left_coin", "shooter_lane", "not_used", "trip_r", "not_used", "left_return", "not_used", "bottom_jet" },
  { "slam_tilt", "not_used", "left_lockup", "trip_i", "drop_target_car", "right_return", "not_used", "left_slingshot" },
  { "high_score_reset", "big_bucks", "not_used", "trip_p", "not_used", "right_outlane", "not_used", "right_slingshot" }
};

buttonController::buttonController()
{
}

buttonController::~buttonController()
{
}

void buttonController::startup(PinIO* _pinio)
{
  pinIo = _pinio;
  for (int c = 0; c < 8; c++){
    for (int r = 0; r < 8; r++){
      buttons[c][r].startup(c, r, ((8 * c) + (r + 1)), buttonNames[r][c]);
    }
  }

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pinIo->pinMode(rowPins[i], INPUT);
    //pinIo->digitalWrite(rowPins[i], LOW); //not necesssary?
  }
  for (int i = 0; i < SIZEOF(colPins); i++){
    pinIo->pinMode(colPins[i], OUTPUT);
    pinIo->digitalWrite(colPins[i], LOW);
  }
}

void buttonController::update(int delta)
{
  //TODO: update the switch flash states based on deltas
  //std::cout << "update";
  //delay(1);

   for (int c = 0; c < 8; c++) //columns
   {
     //set the appropriate output pins for the current column
     for (int i = 0; i < 3; i++)
     {
       pinIo->digitalWrite(colPins[i], colOutputs[c][i]);
     }

     for (int r = 0; r < 8; r++)
     {
       //now for each row!
       buttons[c][r].onOffState = pinIo->digitalRead(rowPins[r]);
     }
   }
}

button *buttonController::getButton(string name){
  for (int c = 0; c < 8; c++){
    for (int r = 0; r < 8; r++){
      if (buttons[c][r].getName() == name){
        return(&buttons[c][r]);
      }
    }
  }
  return(nullptr);
}

bool buttonController::getButtonState(string name){
  button *tmpButton = getButton(name);
  if (NULL != tmpButton){
    return(tmpButton->onOffState);
  }
  return(0);
}

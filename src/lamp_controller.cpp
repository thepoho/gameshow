#include "lamp_controller.h"


const int rowPins[8] = { 0, 2, 3, 12, 13, 14, 21, 22 };
const int colPins[3] = { 8, 9, 7 };
const int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
const string lampNames[8][8] = { 
  {"shoot_again", "bonus_1k", "wheel_5k", "wheel_45k", "truck_t", "big_bucks", "2_million_left", "top_lane_right" },
  {"wheel_5x","bonus_2x","wheel_10k","wheel_50k","truck_r","top_lane_red","left_spot_letter","grand_prize"},
  { "bonus_multiplier_1x", "bonus_4k", "wheel_15k", "tv_t", "truck_u", "top_lane_red", "left_extra_ball", "collect_tv" },
  { "bonus_multiplier_2x", "bonus_8k", "wheel_20k", "tv_v", "truck_c", "back_panel_car", "2_million_right", "collect_trip" },
  { "bonus_multiplier_4x", "bonus_16k", "wheel_25k", "trip_t", "truck_k", "left_extra_ball", "right_spot_letter", "collect_truck" },
  { "bonus_miltiplier_8x", "bonus_32_k", "wheel_30k", "trip_r", "wheel_250k", "wheel_4_million", "right_spinner", "collect_car" },
  { "center_spinner", "bonus_64k", "wheel_35k", "trip_i", "wheel_hold_bonus", "wheel_extra_ball", "top_lane_left", "collect_prizes" },
  { "center_nudge", "bonus_128k", "wheel_40k", "trip_p", "wheel_1_million", "right_extra_ball", "top_lane_middle", "right_lock" }
};

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
      lamps[c][r].startup(c, r, ((8 * c) + (r + 1)), lampNames[r][c]);
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
  //std::cout << "update";
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
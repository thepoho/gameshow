#include "button_controller.h"


static const int rowPins[8] = { 4, 5, 6, 10, 11, 26, 27, 28 };
static const int colPins[3] = { 15, 16, 1 };
static const int colOutputs[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
const string buttonNames[8][8] = {
  { "plum_bob_tilt", "not_used", "top_lane_left", "easy_spin", "truck_t", "spin_wheel", "not_used", "right_flipper" },
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
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      buttons[r][c].startup(r, c, ((8 * r) + (c + 1)), buttonNames[r][c]);
    }
  }

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pinIo->setPinMode(rowPins[i], INPUT);
  }
  for (int i = 0; i < SIZEOF(colPins); i++){
    pinIo->setPinMode(colPins[i], OUTPUT);
    pinIo->pinWrite(colPins[i], LOW);
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
       pinIo->pinWrite(colPins[i], colOutputs[c][i]);
     }

     for (int r = 0; r < 8; r++)
     {
       //now for each row!
       buttons[r][c].onOffState = pinIo->pinRead(rowPins[r]);
     }
   }
}

button *buttonController::getButton(string name){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (buttons[c][r].getName() == name){
        return(&buttons[r][c]);
      }
    }
  }
  return(NULL);
}

bool buttonController::getButtonState(string name){
  button *tmpButton = getButton(name);
  if (NULL != tmpButton){
    return(tmpButton->onOffState);
  }
  return(0);
}

void buttonController::outputButtons(){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      //bool state = buttons[r][c].onOffState;
      //if(state){
        //printf("%s", buttons[r][c].getName());
       // cout << buttons[r][c].getName();
      //}
      printf("%d", buttons[r][c].onOffState);
    }
    printf(" ");
  }
  printf("\r");
}

string buttonController::getInfoString(){
  stringstream sstm;
  sstm << "[";
  // string ret = "";

  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      sstm << "{";
      sstm << "\"name\": \"" << buttons[r][c].getName() << "\",";
      sstm << "\"num\": \""  << buttons[r][c].getNum()  << "\",";
      sstm << "\"row\": \""  << buttons[r][c].getRow()  << "\",";
      sstm << "\"col\": \""  << buttons[r][c].getCol()  << "\"";
      // sstm <<  buttons[r][c].getNum();
      sstm <<  "}";
      if(!(c == 7 && r == 7)){
        sstm <<  ", ";
      }
    }
  }
  sstm <<  "]";
  return sstm.str();
}
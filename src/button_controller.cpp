#include "button_controller.h"


// static const int colReadPins[8] = { 4, 5, 6, 10, 11, 26, 27, 28 };
static const int colReadPins[8] = { 28,27,26,11,10,6,5,4 };
static const int rowPins[3] = { 15, 16, 1 };
static const int rowOutputs[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } };
// const string buttonNames64[64] = { "plum_bob_tilt", "not_used", "top_lane_left", "easy_spin", "truck_t", "spin_wheel", "not_used", "right_flipper", "not_used", "outhole", "top_lane_middle", "center_ramp", "truck_r", "right_spinner", "not_used", "left_flipper", "credit_button", "trough_1_right", "top_lane_right", "tv_t", "truck_u", "spot_letter", "not_used", "not_used", "right_coin", "trough_2_left", "right_ramp", "tv_v", "truck_c", "not_used", "not_used", "left_jet", "center_coin", "not_used", "ball_popper", "trip_t", "truck_k", "left_outlane", "not_used", "right_jet", "left_coin", "shooter_lane", "not_used", "trip_r", "not_used", "left_return", "not_used", "bottom_jet", "slam_tilt", "not_used", "left_lockup", "trip_i", "drop_target_car", "right_return", "not_used", "left_slingshot", "high_score_reset", "big_bucks", "not_used", "trip_p", "not_used", "right_outlane", "not_used", "right_slingshot" };

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

void buttonController::startup(GameShow* _game_show, PinIO* _pinio)
{
  pinIo = _pinio;
  game_show = _game_show;
  elapsedTime = 0;

  int idx = 0;

  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      // int tmpNum = ((8 * r) + (c));
      cout << "row is " << r << " col is " << c << endl;
      buttons[r][c].startup(r, c, idx, buttonNames[r][c]);

      // buttons64[idx].startup(r, c, idx, buttonNames64[idx]);
      idx++;
    }
  }

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(colReadPins); i++){
    pinIo->setPinMode(colReadPins[i], INPUT);
  }
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pinIo->setPinMode(rowPins[i], OUTPUT);
    pinIo->pinWrite(rowPins[i], LOW);
  }
}

void buttonController::update(unsigned int delta)
{
  elapsedTime += delta;

  for (int r = 0; r < 8; r++){ //For switch matrix, drive the rows, read the columns

    //set the appropriate output pins for the current row
    for (int i = 0; i < 3; i++){
      pinIo->pinWrite(rowPins[i], rowOutputs[r][i]);
    }

    for (int c = 0; c < 8; c++){
      //now read each column

      int gotPinState = pinIo->pinRead(colReadPins[c]);
      bool stateChanged = buttons[r][c].setState(gotPinState);
      
      
      if(stateChanged){
	      //TODO - make it so we can turn off the web stuff at run time with a flag
        cout << "State changed R:" << r << " C:" << c << " name: " << buttons[r][c].getName() << " idx: " << buttons[r][c].getNum();
        updateWebButtonState(buttons[r][c]);
      }
    }
  }
}

button *buttonController::getButton(string name){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (buttons[r][c].getName() == name){
        return(&buttons[r][c]);
      }
    }
  }
  return(NULL);
}

// button *buttonController::getbutton(buttonName name){

// }

bool buttonController::getButtonState(string name){
  button *tmpButton = getButton(name);
  if (NULL != tmpButton){
    return(tmpButton->getState());
  }
  return(0);
}

void buttonController::outputButtons(){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      printf("%d", buttons[r][c].getState());
    }
    printf(" ");
  }
  printf("\r");
}

void buttonController::updateWebButtonState(button _btn)
{

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("button_state");
  writer.String("data");
  _btn.serializeJson(&writer);
  writer.EndObject();

  game_show->sendWebMessage(s.GetString());
}

string buttonController::getInfoString(){

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("get_buttons");
  writer.String("data");
  writer.StartArray();

  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      buttons[r][c].serializeJson(&writer);
    }
  }
  writer.EndArray();
  writer.EndObject();

  return s.GetString();
}

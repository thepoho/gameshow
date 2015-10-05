#include "lamp_controller.h"


int rowPins[8] = { 22,21,14,13,12,3,2,0 };
int colPins[3] = { 8, 9, 7 };
int colOutputs[8][3] = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 0 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 0, 0 } };
string lampNames[8][8] = { 
  {"shoot_again", "bonus_1k", "wheel_5k", "wheel_45k", "truck_t", "big_bucks", "2_million_left", "top_lane_right" },
  {"wheel_5x","bonus_2x","wheel_10k","wheel_50k","truck_r","top_lane_red","left_spot_letter","grand_prize"},
  { "bonus_multiplier_1x", "bonus_4k", "wheel_15k", "tv_t", "truck_u", "top_lane_red_1", "left_extra_ball", "collect_tv" },
  { "bonus_multiplier_2x", "bonus_8k", "wheel_20k", "tv_v", "truck_c", "back_panel_car", "2_million_right", "collect_trip" },
  { "bonus_multiplier_4x", "bonus_16k", "wheel_25k", "trip_t", "truck_k", "left_extra_ball", "right_spot_letter", "collect_truck" },
  { "bonus_miltiplier_8x", "bonus_32_k", "wheel_30k", "trip_r", "wheel_250k", "wheel_4_million", "right_spinner", "collect_car" },
  { "center_spinner", "bonus_64k", "wheel_35k", "trip_i", "wheel_hold_bonus", "wheel_extra_ball", "top_lane_left", "collect_prizes" },
  { "center_nudge", "bonus_128k", "wheel_40k", "trip_p", "wheel_1_million", "right_extra_ball", "top_lane_middle", "right_lock" }
};

LampController::LampController()
{
  elapsedTime = 0;
  lastFastFlash = 0;
  fastFlashStatus = 0;
  lastSlowFlash = 0;
  slowFlashStatus = 0;
}

LampController::~LampController()
{
}

void LampController::startup(GameShow* _game_show, PinIO* _pinio)
{
  pinIo = _pinio;
  game_show = _game_show;
  int idx = 0;

  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      lamps[r][c].startup(r, c, idx++, lampNames[r][c]);
    }
  }

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pinIo->setPinMode(rowPins[i], OUTPUT);
    pinIo->pinWrite(rowPins[i], LOW);
  }
  for (int i = 0; i < SIZEOF(colPins); i++){
    pinIo->setPinMode(colPins[i], OUTPUT);
    pinIo->pinWrite(colPins[i], LOW);
  }
}

void LampController::update(unsigned int delta)
{
  elapsedTime += delta;
  
  if (elapsedTime >= (lastFastFlash + FAST_FLASH_DELAY)){
    lastFastFlash = elapsedTime;
    fastFlashStatus = !fastFlashStatus;
  }

  if (elapsedTime >= (lastSlowFlash + SLOW_FLASH_DELAY)){
    lastSlowFlash = elapsedTime;
    slowFlashStatus = !slowFlashStatus;
  }
  flushLamps();
}

void LampController::flushLamps()
{
  for (int c = 0; c < 8; c++)
  { //columns

    //turn all rows off. Mabe unnecessary?
    for(int i = 0; i < SIZEOF(rowPins); i++){
      pinIo->pinWrite(rowPins[i], LOW);
    }

    //set the appropriate output pins for the current column
    for (int i = 0; i < 3; i++){
      pinIo->pinWrite(colPins[i], colOutputs[c][i]);
    }

    for (int r = 0; r < 8; r++){
      //now for each row!
      Lamp tmpLamp = lamps[r][c];
      int state = 0;
      switch (tmpLamp.getState())
      {
      case LAMP_ON:
        state = 1;
        break;
      case LAMP_FLASH_FAST:
        state = fastFlashStatus;
        break;
      case LAMP_FLASH_SLOW:
        state = slowFlashStatus;
        break;
      default: //AKA LAMP_OFF
        state = 0;
        break;
      }
      pinIo->pinWrite(rowPins[r], state);
    }
    pinIo->doDelay(1);
  }
}

Lamp *LampController::getLamp(string name){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (lamps[r][c].getName().compare(name) == 0){
        return(&lamps[r][c]);
      }
    }
  }
  return(NULL);
}

void LampController::setLampState(string name, LampState state){
  if(name.compare("all") == 0 ){
    for (int r = 0; r < 8; r++){
      for (int c = 0; c < 8; c++){
        if(lamps[r][c].setState(state)){
          updateWebLampState(&lamps[r][c]);
        }
      }
    }
  }else{
    Lamp *tmpLamp = getLamp(name);
    if (NULL != tmpLamp){
      if(tmpLamp->setState(state)){
        updateWebLampState(tmpLamp);
      }
    }
  }
}



void LampController::updateWebLampState(Lamp* _lmp)
{

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("lamp_state");
  writer.String("data");
  _lmp->serializeJson(&writer);
  writer.EndObject();

  game_show->sendWebMessage(s.GetString());
}

string LampController::getInfoString(){

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("get_lamps");
  writer.String("data");
  writer.StartArray();

  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      lamps[r][c].serializeJson(&writer);
    }
  }
  writer.EndArray();
  writer.EndObject();

  return s.GetString();
}
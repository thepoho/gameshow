#include "coil_controller.h"

string coilNames[COIL_COUNT] = {"r_flipper","l_flipper",
                      "bottom_jet","right_jet","right_kicker","left_kicker","left_jet",
                      "title_flasher","backbox_gi_relay","ball_popper","centre_ramp_flasher","top_ramp_gate","playfield_gi_relay",
                      "car_drop_target","knocker","ball_locker","ball_shooter_lane_feeder","outhole_kicker"};


coilController::coilController()
{
  elapsedTime = 0;
}

coilController::~coilController()
{
}

void coilController::startup(GameShow* _game_show, PinIO* _pinio)
{
  pinIo = _pinio;
  game_show = _game_show;
  //create all my coils                    
  for(int i = 0; i < SIZEOF(coils); i++){
    coils[i].startup(i, coilNames[i]);
    
    //all coils should turn off after a period of time except for flippers
    if(coilNames[i] == "r_flipper" || coilNames[i] == "l_flipper"){
      coils[i].setShouldTurnOff(FALSE);
    }

  }
}

void coilController::update(unsigned int delta)
{
  elapsedTime += delta;
  // printf("elapsed time is %d\n", elapsedTime);
  
  //See if any coils have been on for too long and turn them off
  for(int i = 0; i < SIZEOF(coils); i++){
    // if(i == 5){
    //   printf("coil state is %d\n", coils[i].getState());
    //   // printf("coil tot   is %d\n", coils[i].getTurnOffTime());
    // }
    if(coils[i].update(delta)){
      //The coil state has changed. Probably due to an auto switch off.
      pinIo->setSerialOutput(coils[i].getNumber(), coils[i].getState());
      updateWebCoilState(coils[i]);
    }
  }  
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
      updateWebCoilState(*tmpCoil);
      // tmpCoil->setTurnOffTime(elapsedTime + COIL_ON_TIME);
    }
  }
}

string coilController::getInfoString(){

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("get_coils");
  writer.String("data");
  writer.StartArray();

  for(int i = 0; i < SIZEOF(coils); i++){
    coils[i].serializeJson(&writer);
  }
  writer.EndArray();
  writer.EndObject();

  return s.GetString();
}

void coilController::updateWebCoilState(coil _coil)
{

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("coil_state");
  writer.String("data");
  _coil.serializeJson(&writer);
  writer.EndObject();

  game_show->sendWebMessage(s.GetString());
}

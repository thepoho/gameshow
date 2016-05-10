#include "coil_controller.h"

string coilNames[COIL_COUNT] = {"left_flipper","right_flipper",
                      "bottom_jet","right_jet","right_slingshot","left_slingshot","left_jet",
                      "title_flasher","backbox_gi_relay","playfield_gi_relay","centre_ramp_flasher","top_ramp_gate","ball_popper",
                      "outhole_kicker","ball_shooter_lane_feeder","ball_locker","knocker","car_drop_target"};
//*/

CoilController::CoilController()
{
  elapsedTime = 0;
  allState = 0;
}

CoilController::~CoilController()
{
  delete[] coils;
}

void CoilController::startup(PinIO* _pinio, SocketServer* _socket_server)
{
  pPinIo = _pinio;
  // game_show = _game_show;
  pSocketServer = _socket_server;
  //create all my coils                    

  /*
  for(int i = 0; i < SIZEOF(coils); i++){
    coils[i].startup(i, coilNames[i]);
    
    //all coils should turn off after a period of time except for flippers
    if(coilNames[i] == "right_flipper" || coilNames[i] == "left_flipper"){
      coils[i].setShouldTurnOff(FALSE);
    }

  }
  */
  cout << " coil controller startup " << endl;
  loadCoilsFromFile();
}

void CoilController::loadCoilsFromFile()
{
  ifstream file(COIL_DATA_FILE, ios::in|ios::binary|ios::ate);

  streampos size;
  size = file.tellg();
  char *buffer;
  buffer = new char[size];

  file.seekg (0, ios::beg);
  file.read (buffer, size);
  file.close();

  buffer[size] = 0;

  Document *document = new Document();
  document->Parse(buffer);

  cout << buffer << endl;

  if(document->IsObject()){
    int defaultOnTime = document->FindMember("defaults")->value["on_time"].GetInt();
    int defaultCoolDownTime = document->FindMember("defaults")->value["cool_down_time"].GetInt();
    const Value& a =  document->FindMember("coils")->value;


    assert(a.Size() < 200); //arbitrarily limiting malloc to 200 records JUST IN CASE
    coils = new Coil[a.Size()];

    for (SizeType i = 0; i < a.Size(); i++){
      int idx      = a[i]["index"].GetInt();
      string coilType = a[i]["type"].GetString();
      string name  = a[i]["name"].GetString();
      
      int onTime = defaultOnTime;
      if(a[i].HasMember("on_time")){
        onTime = a[i]["on_time"].GetInt();
      }
      int coolDownTime = defaultCoolDownTime;
      if(a[i].HasMember("cool_down_time")){
        coolDownTime = a[i]["cool_down_time"].GetInt();
      }
      //coils[idx] = new Coil();
      coils[idx].startup(idx, name, onTime, coolDownTime);
      //int c = a[i]["column"].GetInt();
      //buttons[r][c].startup(r, c, idx++, name);
      //cout << a[i]["name"].GetString() << endl;
    }
  }
  delete[] buffer;
  delete(document);
}

void CoilController::setAllState(bool state){
  allState = state;  
}

void CoilController::update(unsigned int delta)
{
  elapsedTime += delta;

  // bool dirty = false;

  //See if any coils have been on for too long and turn them off
  for(int i = 0; i < SIZEOF(coils); i++){
    if(coils[i].update(delta)){
      //The coil state has changed. Probably due to an auto switch off.
      pPinIo->setSerialOutput(coils[i].getNumber(), coils[i].getState());
      updateWebCoilState(coils[i]);
      // dirty = true;
    }
  }
  // if(dirty){
    pPinIo->flushSerialData();
  // }
}


Coil *CoilController::getCoil(string name){
  for(int i = 0; i < SIZEOF(coils); i++){
    if(coils[i].getName() == name){
      return(&coils[i]);
    }
  }
  return(NULL);
}

void CoilController::fireCoil(string name){
  setCoilState(name, COIL_ON);
}

void CoilController::setCoilState(string name, bool state){
  Coil *tmpCoil = getCoil(name);
  if (NULL != tmpCoil){
    if(tmpCoil->setState(state)){
      //will return true if state changed
      pPinIo->setSerialOutput(tmpCoil->getNumber(), tmpCoil->getState());
      updateWebCoilState(*tmpCoil);
      // tmpCoil->setTurnOffTime(elapsedTime + COIL_ON_TIME);
    }
  }
}

string CoilController::getInfoString(){

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

void CoilController::updateWebCoilState(Coil _coil)
{

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("coil_state");
  writer.String("data");
  _coil.serializeJson(&writer);
  writer.EndObject();

  pSocketServer->enqueueMessage(s.GetString());
}

#include "lamp_controller.h"


int rowPins[8] = { 22,21,14,13,12,3,2,0 };
int colPins[3] = { 8, 9, 7 };
int colOutputs[8][3] = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 0 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 0, 0 } };

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

void LampController::startup(PinIO* _pinio, SocketServer* _socket_server)
{
  pPinIo = _pinio;
  // game_show = _game_show;
  pSocketServer = _socket_server;

  loadLampsFromFile();

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pPinIo->setPinMode(rowPins[i], OUTPUT);
    pPinIo->pinWrite(rowPins[i], LOW);
  }
  for (int i = 0; i < SIZEOF(colPins); i++){
    pPinIo->setPinMode(colPins[i], OUTPUT);
    pPinIo->pinWrite(colPins[i], LOW);
  }
}


void LampController::loadLampsFromFile()
{
  ifstream file(LAMP_DATA_FILE, ios::in|ios::binary|ios::ate);

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

  // cout << buffer << endl;

  if(document->IsObject()){
    const Value& a =  document->FindMember("lamps")->value;
    int idx = 0;
    for (SizeType i = 0; i < a.Size(); i++){
      int r = a[i]["row"].GetInt();
      int c = a[i]["column"].GetInt();
      string name = a[i]["name"].GetString();
      lamps[r][c].startup(r, c, idx++, name);
      // cout << a[i]["name"].GetString() << endl;
    }
  }
  delete[] buffer;
  delete(document);
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
      pPinIo->pinWrite(rowPins[i], LOW);
    }

    //set the appropriate output pins for the current column
    for (int i = 0; i < 3; i++){
      pPinIo->pinWrite(colPins[i], colOutputs[c][i]);
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
      pPinIo->pinWrite(rowPins[r], state);
    }
    pPinIo->doDelay(1);
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

  pSocketServer->enqueueMessage(s.GetString());
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

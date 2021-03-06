#include "button_controller.h"


// static const int colReadPins[8] = { 4, 5, 6, 10, 11, 26, 27, 28 };
static const int colReadPins[8] = { 28,27,26,11,10,6,5,4 };
static const int rowPins[3] = { 15, 16, 1 };
static const int rowOutputs[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } };

ButtonController::ButtonController()
{
}

ButtonController::~ButtonController()
{
}

void ButtonController::startup(PinIO* _pinio, SocketServer* _socket_server)
{
  pPinIo = _pinio;
  // game_show = _game_show;
  pSocketServer = _socket_server;
  elapsedTime = 0;

  loadButtonsFromFile();

  //initialize the pins on the rpi
  for (int i = 0; i < SIZEOF(colReadPins); i++){
    pPinIo->setPinMode(colReadPins[i], INPUT);
  }
  for (int i = 0; i < SIZEOF(rowPins); i++){
    pPinIo->setPinMode(rowPins[i], OUTPUT);
    pPinIo->pinWrite(rowPins[i], LOW);
  }
}

void ButtonController::loadButtonsFromFile()
{
  ifstream file(BUTTON_DATA_FILE, ios::in|ios::binary|ios::ate);

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
    const Value& a =  document->FindMember("buttons")->value;
    int idx = 0;
    for (SizeType i = 0; i < a.Size(); i++){
      int r = a[i]["row"].GetInt();
      int c = a[i]["column"].GetInt();
      string name = a[i]["name"].GetString();
      buttons[r][c].startup(r, c, idx++, name);
      //cout << a[i]["name"].GetString() << endl;
    }
  }
  delete[] buffer;
  delete(document);
}

void ButtonController::update(unsigned int delta)
{
  elapsedTime += delta;

  for (int r = 0; r < 8; r++){ //For switch matrix, drive the rows, read the columns

    //set the appropriate output pins for the current row
    for (int i = 0; i < 3; i++){
      pPinIo->pinWrite(rowPins[i], rowOutputs[r][i]);
    }

    for (int c = 0; c < 8; c++){
      //now read each column

      int gotPinState = pPinIo->pinRead(colReadPins[c]);


      if(gotPinState != buttons[r][c].getState()){//the button state has changed.
        if(canUpdateButton(&buttons[r][c])){ //ensure the button is not in cooldown.
          usleep(5); //sleep for 5 micros and check again (cheap debouncing)
          if(gotPinState == pPinIo->pinRead(colReadPins[c])){
            setButtonState(&buttons[r][c], bool(gotPinState));
          }
        }
      }

    }
  }
}

bool ButtonController::canUpdateButton(Button *btn){
  return( (unsigned int)(btn->getLastPressTime() + BUTTON_COOLDOWN_TIME ) < elapsedTime);
}

void ButtonController::setButtonStateByName(string name, bool newState){
  Button *btn = getButton(name);
  if(NULL != btn){
    setButtonState(btn, newState);
  }else{
    cout << "Trying to set state of nonexistant button " << name;
  }
}

void ButtonController::overrideButtonState(string name, bool newState){
  Button *btn = getButton(name);
  if(NULL != btn){
    setButtonState(btn, newState);

    btn->setOverridden(newState); //mark as overridden if set to 'on'. flag will be cleared when released
  }else{
    cout << "Trying to set state of nonexistant button " << name;
  }

}
void ButtonController::setButtonState(Button *btn, bool newState){
  bool stateChanged = btn->setState(newState);

  if(stateChanged){
    btn->setLastPressTime(elapsedTime);
    updateWebButtonState(btn);
  }
}

Button *ButtonController::getButton(string name){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (buttons[r][c].getName() == name){
        return(&buttons[r][c]);
      }
    }
  }
  return(NULL);
}

void ButtonController::resetAllWasPressedReleased()
{
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      buttons[r][c].wasPressed  = false;
      buttons[r][c].wasReleased = false;
    }
  }
}

bool ButtonController::getButtonState(string name){
  Button *tmpButton = getButton(name);
  if (NULL != tmpButton){
    return(tmpButton->getState());
  }
  return(0);
}

void ButtonController::outputButtons(){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      printf("%d", buttons[r][c].getState());
    }
    printf(" ");
  }
  printf("\r");
}

void ButtonController::updateWebButtonState(Button *_btn)
{

  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("button_state");
  writer.String("data");
  _btn->serializeJson(&writer);
  writer.EndObject();

  pSocketServer->enqueueMessage(s.GetString());
}

string ButtonController::getInfoString(){

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

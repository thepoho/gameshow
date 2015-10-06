#include "game_show.h"
//#include "base_game_state.h"

LampController    lamp_controller;
ButtonController  button_controller;
CoilController    coil_controller;
BaseGameState*    pGameState;
PinIO *pPinIo;
SocketServer *pSocketServer;
unsigned int lastTickTime;
  
GameShow::GameShow()
{

  pPinIo = new PinIO();
  
  pPinIo->startup();
  
  pSocketServer = new SocketServer();
  pSocketServer->startup();
  
  button_controller.startup(pPinIo, pSocketServer);
  lamp_controller.startup(pPinIo, pSocketServer);
  coil_controller.startup(pPinIo, pSocketServer);


  // printf("not starting socket server yet!");
  // printf("this pointer is %p\n", this);

  game_state = GS_ATTRACT;

  // pGameState = new BaseGameState();
  // pGameState->startup(this);

  // coil_controller.getCoil("trough")->setState(1);
  printf("setup complete\n");

}

GameShow::~GameShow()
{

}

void GameShow::run(){
  printf("starting main loop\n");
  while(1){
    
  //work out deltas
    unsigned int millis = pPinIo->getMillis();
    unsigned int delta = millis - lastTickTime;
    lastTickTime = millis;

    lamp_controller.update(delta);
    button_controller.update(delta);
    coil_controller.update(delta);
    processWebMessages();

    // pGameState->update(delta);

    switch(game_state){
      case GS_OFF:
        break;
      case GS_ATTRACT:
        //nothing yet
        break;
      case GS_PLAYING:
        doAutoCoils();
        break;
      case GS_DEBUG:
        // doDebug();
        break;
    }
  }
}

void GameShow::doAutoCoils(){
  if (button_controller.getButtonState("right_flipper")){
    coil_controller.setCoilState("right_flipper", COIL_ON);
    // lamp_controller.setLampState("truck_t", LAMP_ON);
  }
  else{
    coil_controller.setCoilState("right_flipper", COIL_OFF);
    // lamp_controller.setLampState("truck_t", LAMP_OFF);
  }

  if (button_controller.getButtonState("left_flipper")){
    coil_controller.setCoilState("left_flipper", COIL_ON);
    // lamp_controller.setLampState("truck_r", LAMP_ON);
  }
  else{
    coil_controller.setCoilState("left_flipper", COIL_OFF);
    // lamp_controller.setLampState("truck_r", LAMP_OFF);
  }

  if (button_controller.getButtonState("left_jet")){
    coil_controller.setCoilState("left_jet", COIL_ON);
  }
  if (button_controller.getButtonState("right_jet")){
    coil_controller.setCoilState("right_jet", COIL_ON);
  }
  if (button_controller.getButtonState("bottom_jet")){
    coil_controller.setCoilState("bottom_jet", COIL_ON);
  }
  if (button_controller.getButtonState("left_slingshot")){
    coil_controller.setCoilState("left_slingshot", COIL_ON);
  }
  if (button_controller.getButtonState("right_slingshot")){
    coil_controller.setCoilState("right_slingshot", COIL_ON);
  }

}

void GameShow::sendWebMessage(string message)
{
  pSocketServer->enqueueMessage(message);
}

void GameShow::processWebMessages()
{
  Document* document = pSocketServer->getNextIncomingMessage();
  if(0 != document){
    cout << "Got document " << document;
    
    string message = document->FindMember("message")->value.GetString();
    cout << "Got message " << document;

    if(message.compare("get_buttons") == 0){
      sendWebMessage(button_controller.getInfoString());
    
    }else if(message.compare("get_lamps") == 0){
      sendWebMessage(lamp_controller.getInfoString());
    
    }else if(message.compare("get_coils") == 0){
      sendWebMessage(coil_controller.getInfoString());
    
    }else if(message.compare("set_lamp_state") == 0){
      string name = document->FindMember("name")->value.GetString();
      LampState state = (LampState)document->FindMember("value")->value.GetInt();
      lamp_controller.setLampState(name, state);
    
    }else if(message.compare("set_coil_state") == 0){
      string name = document->FindMember("name")->value.GetString();
      int state = document->FindMember("value")->value.GetInt();
      coil_controller.setCoilState(name, state);

    }else if(message.compare("get_game_state") == 0){
      sendGameStateToWeb();

    }else if(message.compare("set_game_state") == 0){
      GameState state = (GameState)document->FindMember("value")->value.GetInt();
      setGameState(state);
    }
    
    free(document);
  }
}

void GameShow::sendGameStateToWeb(){
  StringBuffer s;
  Writer<StringBuffer> writer(s);

  writer.StartObject();
  writer.String("name");
  writer.String("game_state");
  writer.String("data");

  writer.StartObject();
  writer.String("value");
  writer.Uint((unsigned int) game_state);
  writer.EndObject();
  
  writer.EndObject();

  sendWebMessage(s.GetString());
}

void GameShow::setGameState(GameState _state){
  game_state = _state;
  sendGameStateToWeb();
}
#include "game_show.h"
  
GameShow::GameShow()
{

  pGameController = new GameController();
  pGameController->startup();


  pGameState = new StateBasic();  // This will eventually be defaulting to something like attract
  pGameState->startup(pGameController);

  printf("setup complete\n");
}

GameShow::~GameShow()
{
  delete(pGameController);
  delete(pGameState);
}

void GameShow::run(){
  printf("starting main loop\n");
  while(1){
    
  //work out deltas
    unsigned int millis = pGameController->pinIO()->getMillis();
    unsigned int delta = millis - lastTickTime;
    lastTickTime = millis;

    pGameController->update(delta);

    processWebMessages();

    pGameState->update(delta);

  }
}


void GameShow::processWebMessages()
{
  Document* document = pGameController->socketServer()->getNextIncomingMessage();
  if(0 != document){
    // cout << "Got document " << document;
    
    string message = document->FindMember("message")->value.GetString();
    // cout << "Got message " << document;

    if(message.compare("get_buttons") == 0){
      pGameController->sendWebMessage(pGameController->buttonController()->getInfoString());
    
    }else if(message.compare("get_lamps") == 0){
      pGameController->sendWebMessage(pGameController->lampController()->getInfoString());
    
    }else if(message.compare("get_coils") == 0){
      pGameController->sendWebMessage(pGameController->coilController()->getInfoString());
    
    }else if(message.compare("set_lamp_state") == 0){
      string name = document->FindMember("name")->value.GetString();
      LampState state = (LampState)document->FindMember("value")->value.GetInt();
      pGameController->lampController()->setLampState(name, state);
    
    }else if(message.compare("set_coil_state") == 0){
      string name = document->FindMember("name")->value.GetString();
      int state = document->FindMember("value")->value.GetInt();
      pGameController->coilController()->setCoilState(name, state);

    }else if(message.compare("get_game_states") == 0){
      //note the plural S
      // pGameState->sendToWeb();
    }else if(message.compare("get_game_state") == 0){
      pGameState->sendToWeb();

    }else if(message.compare("set_game_state") == 0){
      string state = document->FindMember("value")->value.GetString();
      setGameState(state);
    }
    
    //I don't like this here.
    delete(document);
  }
}


void GameShow::setGameState(string _state){
  if(_state.compare("debug") == 0){
    StateCore *tmp_state = new StateDebug();
    doSetNewGameState(tmp_state);
  }
  if(_state.compare("basic") == 0){
    StateCore *tmp_state = new StateBasic();
    doSetNewGameState(tmp_state);  
  }
  pGameState->sendToWeb();
}

void GameShow::doSetNewGameState(StateCore *_new_state){
  delete(pGameState);
  pGameState = _new_state;
  pGameState->startup(pGameController);
}
#include "web_message_handler.h"
  
WebMessageHandler::WebMessageHandler()
{
}

WebMessageHandler::~WebMessageHandler()
{
}

void WebMessageHandler::startup(GameController* _game_controller)
{
  pGameController = _game_controller;
}


void WebMessageHandler::processWebMessages(Document* document)
{
  // Document* document = pGameController->socketServer()->getNextIncomingMessage();
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

    }/*else if(message.compare("get_game_state") == 0){
      pGameState->sendToWeb();

    }else if(message.compare("set_game_state") == 0){
      GameState state = (GameState)document->FindMember("value")->value.GetInt();
      setGameState(state);
    }*/

  }
}
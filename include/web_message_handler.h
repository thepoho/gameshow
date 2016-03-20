#ifndef _WEB_MESSAGE_HANDLER_H
#define _WEB_MESSAGE_HANDLER_H

#include "common_defines.h"
#include "game_controller.h"

class WebMessageHandler
{
public:
  WebMessageHandler();
  ~WebMessageHandler();

  void startup(GameController* _game_controller);

  void processWebMessages(Document* document);
  
private:
  GameController* pGameController;
};

#endif //_WEB_MESSAGE_HANDLER_H
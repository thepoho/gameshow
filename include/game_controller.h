#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "lamp_controller.h"
#include "button_controller.h"
#include "coil_controller.h"
#include "delayed_event_controller.h"

#include "socket_server.h"
#include "pin_io.h"
// #include "game_show.h"

class GameController
{
public:
  GameController();
  ~GameController();

  void startup();

  void update(unsigned int delta);

  PinIO* pinIO() { return pPinIo; }
  SocketServer*             socketServer()           { return pSocketServer; }
  CoilController*           coilController()         { return pCoilController; }
  LampController*           lampController()         { return pLampController; }
  ButtonController*         buttonController()       { return pButtonController; }
  DelayedEventController*   delayedEventController() { return pDelayedEventController; }

  void sendWebMessage(string message);
  
private:

  void processWebMessages();
  void processDelayedEvents();

  PinIO* pPinIo;
  SocketServer* pSocketServer;

  CoilController*         pCoilController;
  LampController*         pLampController;
  ButtonController*       pButtonController;
  DelayedEventController* pDelayedEventController;

  // WebMessageHandler*  pWebMessageHandler;

};

#endif

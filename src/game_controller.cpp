#include "game_controller.h"

GameController::GameController()
{
}

GameController::~GameController()
{
  delete(pPinIo);
  delete(pSocketServer);
  delete(pButtonController);
  delete(pLampController);
  delete(pCoilController);
  delete(pDelayedEventController);
}

void GameController::startup()
{
  pPinIo = new PinIO();
  pPinIo->startup();
  
  pSocketServer = new SocketServer();
  pSocketServer->startup();
  
  pButtonController = new ButtonController();
  pButtonController->startup(pPinIo, pSocketServer);
  
  pLampController = new LampController();
  pLampController->startup(pPinIo, pSocketServer);
  
  pCoilController = new CoilController();
  pCoilController->startup(pPinIo, pSocketServer);

  pDelayedEventController = new DelayedEventController();
  pDelayedEventController->startup();
}

void GameController::update(unsigned int delta)
{
  // pPinIo->update(delta);
  // pSocketServer->update(delta);

  pCoilController->update(delta);
  pLampController->update(delta);
  pButtonController->update(delta);

  pDelayedEventController->update(delta);
  processDelayedEvents();
}

void GameController::sendWebMessage(string message)
{
  pSocketServer->enqueueMessage(message);
}

void GameController::processDelayedEvents()
{
  //TODO: put this in a loop so all due events are processed
  DelayedEvent *tmp = pDelayedEventController->getDueEvent();
  if(NULL != tmp){
    //run the event
    cout << "GOT AN EVENT " << tmp->getEventType() << endl;
    pDelayedEventController->freeEvent(tmp);
  }
}

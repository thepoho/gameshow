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
}

void GameController::update(unsigned int delta)
{
  // pPinIo->update(delta);
  // pSocketServer->update(delta);

  pCoilController->update(delta);
  pLampController->update(delta);
  pButtonController->update(delta);

}

void GameController::sendWebMessage(string message)
{
  pSocketServer->enqueueMessage(message);
}
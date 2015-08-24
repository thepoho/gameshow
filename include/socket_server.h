#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#include "common_defines.h"

#include "game_show.h"

using namespace std;

#include <thread>
#include <string.h>

class socketServer
{
public:
  socketServer();
  ~socketServer();
  static void startup(GameShow* _gameshow);
  // void startup();


  
private:

  static int ev_handler(struct mg_connection *conn, enum mg_event ev);
  static void runThread();

  static int sendWsReply(struct mg_connection *conn);

  // std::thread socketThread;

  static GameShow* gameShow;
  
};

#endif //_SOCKET_SERVER_H
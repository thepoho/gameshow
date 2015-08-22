#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#include "common_defines.h"

#include <thread>

class socketServer
{
public:
  socketServer();
  ~socketServer();
  void startup();


  
private:

  static int ev_handler(struct mg_connection *conn, enum mg_event ev);
  static void runThread();

  std::thread socketThread;
  
};

#endif //_SOCKET_SERVER_H
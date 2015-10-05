#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#include "common_defines.h"

#include "game_show.h"

using namespace std;

#include <thread>
#include <string.h>
#include <queue>
#include <mutex>

class SocketServer
{
public:
  SocketServer();
  ~SocketServer();
  static void startup(GameShow* _gameshow);

  static void sendMessage(string message);
  // void startup();

  static void enqueueMessage(string message);



  
private:

  static int ev_handler(struct mg_connection *conn, enum mg_event ev);
  static void runThread();

  static int sendWsReply(struct mg_connection *conn);
  static string dequeueMessage();
  static void messagePusher();

  // std::thread socketThread;

  static GameShow* gameShow;
  static struct mg_server *s_server;
  static queue<string> messages;

  static mutex queueMutex;
  
};

#endif //_SOCKET_SERVER_H
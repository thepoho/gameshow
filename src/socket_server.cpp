#include "socket_server.h"

socketServer::socketServer()
{
}

socketServer::~socketServer()
{
}

void socketServer::startup()
{
  printf("starting up server\n");
  std::thread t1(socketServer::runThread);
  t1.join();
}

void socketServer::runThread(){
  printf("at run thread\n");
   struct mg_server *server;

  // Create and configure the server
  server = mg_create_server(NULL, socketServer::ev_handler);
  mg_set_option(server, "listening_port", "8080");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&server);
}


int socketServer::ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      mg_printf_data(conn, "Hello! Requested URI is [%s]", conn->uri);
      return MG_TRUE;
    default: return MG_FALSE;
  }
}
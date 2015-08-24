#include "socket_server.h"

GameShow* socketServer::gameShow;

socketServer::socketServer()
{
}

socketServer::~socketServer()
{
}


void socketServer::startup(GameShow* _gameshow)
{
  gameShow = _gameshow;
  // printf("_gameshow pointer is %p\n", _gameshow);
  // printf("gameShow pointer is %p\n", gameShow);
  // printf("starting up server\n");
  std::thread t1(socketServer::runThread);
  t1.detach();
}

void socketServer::runThread(){
  // printf("at run thread\n");
   struct mg_server *server;

  // Create and configure the server
  server = mg_create_server(NULL, socketServer::ev_handler);
  mg_set_option(server, "document_root", "./public_html");
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
      if(!strcmp(conn->uri, "/ws")){
        return sendWsReply(conn);
      }else{
        printf("%s\n",conn->uri);
        return MG_FALSE;
      }
    default: return MG_FALSE;
  }
}

int socketServer::sendWsReply(struct mg_connection *conn)
{
  if(conn->is_websocket){
    // printf("WS: %s\n", conn->content);
    if(!memcmp(conn->content, "get_buttons", 11)){
      //get switch deets
      string info = gameShow->getButtonInfoString();
      info = "{\"name\": \"get_buttons\", \"data\": " + info + "}";
      mg_websocket_write(conn, 1, info.c_str(), info.length());
    }else{
      // printf("gwar");
      mg_websocket_write(conn, 1, "not exit", 8);
    }
    return MG_TRUE ;
  }else{
    return MG_FALSE;
  }
}
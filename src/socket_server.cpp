#include "socket_server.h"

GameShow* socketServer::gameShow;
struct mg_server* socketServer::s_server = NULL;
queue<string> socketServer::messages;
mutex socketServer::queueMutex;

socketServer::socketServer()
{
}

socketServer::~socketServer()
{
}

void socketServer::enqueueMessage(string message){
  queueMutex.lock();
  messages.push(message);
  queueMutex.unlock();
}

string socketServer::dequeueMessage(){
  // string ret;
  // strcpy(ret, messages.pop());
  // return ret;
  return "";
}

void socketServer::messagePusher(){
  while(1){
    string tmp = "";
    if(NULL != s_server){
      queueMutex.lock();
      if(!messages.empty()){
        tmp = messages.front();
        messages.pop();
      }
      queueMutex.unlock();
      if(strcmp("", tmp.c_str())){
        sendMessage(tmp);
      }
    }
  }
}


void socketServer::startup(GameShow* _gameshow)
{
  gameShow = _gameshow;
  // printf("_gameshow pointer is %p\n", _gameshow);
  // printf("gameShow pointer is %p\n", gameShow);
  // printf("starting up server\n");
  std::thread t1(socketServer::runThread);
  t1.detach();

  std::thread t2(socketServer::messagePusher);
  t2.detach();
}

void socketServer::runThread(){
  // printf("at run thread\n");
   // struct mg_server *server;

  // Create and configure the server
  s_server = mg_create_server(NULL, socketServer::ev_handler);
  mg_set_option(s_server, "document_root", "./public_html");
  mg_set_option(s_server, "listening_port", "8080");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(s_server, "listening_port"));
  for (;;) {
    mg_poll_server(s_server, 100);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&s_server);
}

void socketServer::sendMessage(string message)
{
  cout << "Trying to send " << message << endl;
  if(NULL != s_server){
    struct mg_connection *c;
    for (c = mg_next(s_server, NULL); c != NULL; c = mg_next(s_server, c)) {
      // struct conn_data *d2 = (struct conn_data *) c->connection_param;
      // printf("a\n");
      if (!c->is_websocket){
        continue;
      }
      // printf("b\n");
      // data.c_str(), data.length()
      mg_websocket_printf(c, WEBSOCKET_OPCODE_TEXT, "%s", message.c_str());
      // printf("c\n");
    }
  }
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

    if(!memcmp(conn->content, "get_buttons", 11)){

      //get switch deets
      string data = gameShow->getButtonInfoString();

      mg_websocket_write(conn, 1, data.c_str(), data.length());
    }else{
      // printf("gwar");
      // sendMessage("blah blah blah");
      mg_websocket_write(conn, 1, "not exit", 8);
    }
    return MG_TRUE ;
  }else{
    return MG_FALSE;
  }
}
#include "game_show.h"

int main(int argc, char* argv[]){
  GameShow* pGs = new GameShow();
  if(argc == 2 && std::string(argv[1]) == "--test"){
    pGs->test();
  }else{
    pGs->run();
  }
}

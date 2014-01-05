#include <iostream>
#include <vector>
#include <string>
#include "app.h"

using namespace std;

#define SERVER_MODE 1

void start();

int main () {

  int mode = -1;
  short port = 3003;

  scanf("%d", &mode);

  Server *server = NULL;
  Client *client = NULL;

  SharedMemory *sharedMemory = new SharedMemory();

  if(mode == SERVER_MODE) {
    server = new Server(port, *sharedMemory);
    server->run();
    while(!sharedMemory->gameStatus());
    start();
  }
  else {
    client = new Client("127.0.0.1", port);
    delete client;
  }

  // destroy connection
  if(mode == SERVER_MODE) delete server;
  else delete client;

  return 0;
}

void start() {
  printf("game started!!!!\n");

}

#include <iostream>
#include <vector>
#include <string>
#include "app.h"

using namespace std;

#define SERVER_MODE 1

int main () {

  int mode = -1;

  scanf("%d", &mode);

  Server *server = NULL;
  Client *client = NULL;

  if(mode == SERVER_MODE) {
    server = new Server(3000);
    server->run();
    printf("waiting for client...\n");
    while(1) {

    }
  }
  else {
    client = new Client("127.0.0.1", 3000);
    delete client;
  }

  // destroy connection
  if(mode == SERVER_MODE) delete server;
  else delete client;

  return 0;
}

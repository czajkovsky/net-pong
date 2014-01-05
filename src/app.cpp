#include <iostream>
#include <vector>
#include <string>
#include "app.h"

using namespace std;

int main () {

  int mode = -1;

  cin >> mode;

  if(mode == 1) {
    Server *server = new Server(3000);
    delete server;
  }
  else {
    Client *client = new Client("127.0.0.1", 3000);
    delete client;
  }
  return 0;
}

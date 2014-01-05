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
    // client
  }
  return 0;
}

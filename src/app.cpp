#include <iostream>
#include <vector>
#include <string>
#include "app.h"

int main () {

  Server *server = new Server("3000");

  delete server;

}

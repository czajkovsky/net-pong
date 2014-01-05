#include "client.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

Client::Client(int service_port) {

  printf("creating client...\n");

}

Client::~Client() {
  printf("client destroyed...\n");
}

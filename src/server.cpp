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

#include "Server.h"
#include "SharedMemory.h"


using namespace std;

Server::Server(int service_port, SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
  this->service_port = service_port;
}

void* Server::start_routine() {

  printf("creating server...\n");

  const int QSIZE = 2048;

  string protocol = "tcp";

  char *response = "dupa";

  struct sockaddr_in server_addr, client_addr;

  int sck, rcv_sck, rcv_len;

  memset(&server_addr, 0, sizeof server_addr);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (this->service_port);

  sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  bind (sck, (struct sockaddr*) &server_addr, sizeof server_addr);
  listen (sck, QSIZE);

  while (true) {
    rcv_sck = accept (sck, (struct sockaddr*) &client_addr, (socklen_t*) &rcv_len);
    sharedMemory.startGame();
    cout << rcv_sck << "\n";
    write (rcv_sck, response, strlen(response));
    close(rcv_sck);
  }
  close(sck);

  printf("server created...\n");
}

Server::~Server() {
  printf("server destroyed...\n");
}

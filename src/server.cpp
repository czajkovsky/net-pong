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
#include "Ball.h"
#include "protocol.h"

#define BUFLEN 512
#define QSIZE 1000

using namespace std;

Server::Server(int service_port, SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
  this->service_port = 3009;
}

void* Server::start_routine() {

  struct sockaddr_in server_addr, client_addr;
  int sck, rcv_sck, rcv_len, odp;

  char response[BUFLEN];

  memset(&server_addr, 0, sizeof server_addr);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (this->service_port);

  sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  bind (sck, (struct sockaddr*) &server_addr, sizeof server_addr);
  listen (sck, QSIZE);

  rcv_sck = accept (sck, (struct sockaddr*) &client_addr, (socklen_t*) &rcv_len);

  sharedMemory.startGame();

  unsigned char state[33];

  Ball ball;

  while (sharedMemory.gameStatus()) {
    odp = read (rcv_sck, response, BUFLEN);
    if (odp > 0) {
      sharedMemory.getCurrentState(ball);
      state[0] = BEGIN_MESSAGE;
      ball.send(state, 1);
      // write (1, response, odp);
      write (rcv_sck, state, sizeof(state));
    }
  }
  close(rcv_sck);


}

Server::~Server() {
  printf("server destroyed...\n");
}

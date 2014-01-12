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
  this->service_port = service_port;
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
  Player players[2], new_player;
  int x;

  while (sharedMemory.gameStatus()) {
    odp = read (rcv_sck, state, BUFLEN);
    if (odp > 0) {
      if (state[0] == REQUEST_END) {
        sharedMemory.endGame();
        std::cout << "Game ended by client...\n";
      }
      else {
        new_player.receive(state, 1);
        sharedMemory.getCurrentState(ball, players[0], players[1]);
        sharedMemory.setCurrentState(ball, players[0], new_player);
        state[0] = BEGIN_MESSAGE;
        ball.send(state, 1);
        players[0].send(state, 9);
        write (rcv_sck, state, sizeof(state));
      }
    }
  }

  cout << "Ending on server...\n";
  state[0] = REQUEST_END;
  write (rcv_sck, state, sizeof(state));

  close(rcv_sck);


}

Server::~Server() {
  printf("Server destroyed...\n");
}

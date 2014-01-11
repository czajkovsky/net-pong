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

#include "Client.h"
#include "Ball.h"
#include "Player.h"


#define BUFSIZE 512
#define BUFLEN 512

using namespace std;

Client::Client(char* server, short service_port, SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
  this->service_port = service_port;
  // this->service_address = service_address;
}

void* Client::start_routine() {

  struct sockaddr_in sck_addr;

  std::cout << "port: " << this->service_port << "\n";

  char *server = "127.0.0.1"; /* adres IP pętli zwrotnej */
  char *protocol = "tcp";

  int sck, odp;

  memset (&sck_addr, 0, sizeof sck_addr);
  sck_addr.sin_family = AF_INET;
  inet_aton (server, &sck_addr.sin_addr);
  sck_addr.sin_port = htons (this->service_port);

  if ((sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror ("Unable to create socket...");
    exit (EXIT_FAILURE);
  }

  if (connect (sck, (struct sockaddr*) &sck_addr, sizeof sck_addr) < 0) {
    perror ("No connection...");
    exit (EXIT_FAILURE);
  }

  Ball ball;
  Player players[2];
  int x, y;
  unsigned char state[33];

  sharedMemory.startGame();

  while(sharedMemory.gameStatus()) {
    sharedMemory.getCurrentState(ball, players[0], players[1]);
    players[1].send(state, 1);
    write (sck, state, sizeof(state));
    odp = read (sck, state, BUFSIZE);
    if (odp > 0) {
      sharedMemory.getCurrentState(ball, players[0], players[1]);
      ball.receive(state, 1);
      players[0].receive(state, 9);
      sharedMemory.setCurrentState(ball, players[0], players[1]);
    }
  }
  close (sck);

  exit (EXIT_SUCCESS);

}

Client::~Client() {
  printf("client destroyed...\n");
}

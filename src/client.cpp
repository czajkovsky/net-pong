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

Client::Client(char* server, int service_port, SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
  // this->service_port = service_port;
  // this->service_address = service_address;
}

void* Client::start_routine() {

  struct sockaddr_in sck_addr;

  char *server = "127.0.0.1"; /* adres IP pętli zwrotnej */
  char *protocol = "tcp";
  short service_port = 3009;

  int sck, odp;

  memset (&sck_addr, 0, sizeof sck_addr);
  sck_addr.sin_family = AF_INET;
  inet_aton (server, &sck_addr.sin_addr);
  sck_addr.sin_port = htons (service_port);

  if ((sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror ("Unable to create socket...");
    exit (EXIT_FAILURE);
  }

  if (connect (sck, (struct sockaddr*) &sck_addr, sizeof sck_addr) < 0) {
    perror ("No connection...");
    exit (EXIT_FAILURE);
  }

  Ball ball;
  int x, y;
  unsigned char bufor[33];

  sharedMemory.startGame();

  while(sharedMemory.gameStatus()) {
    write (sck, "connection", sizeof("connection"));
    odp = read (sck, bufor, BUFSIZE);
    if (odp > 0) {
      ball.receive(bufor, 1);
      ball.getPosition(x, y);
      sharedMemory.setCurrentState(ball);
      std::cout << x << "\n";
    }
  }
  close (sck);

  exit (EXIT_SUCCESS);

}

Client::~Client() {
  printf("client destroyed...\n");
}

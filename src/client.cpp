#include "Client.h"
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

#define BUFSIZE 10000

using namespace std;

Client::Client(char* server, int service_port) {

  printf("creating client...\n");

  struct sockaddr_in sck_addr;

  int sck, odp;

  char bufor[BUFSIZE];


  memset (&sck_addr, 0, sizeof sck_addr);
  sck_addr.sin_family = AF_INET;
  inet_aton (server, &sck_addr.sin_addr);
  sck_addr.sin_port = htons (service_port);

  if ((sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror ("Unable to create socket\n");
    exit (EXIT_FAILURE);
  }

  if (connect (sck, (struct sockaddr*) &sck_addr, sizeof sck_addr) < 0) {
    perror ("Unable to connect\n");
    exit (EXIT_FAILURE);
  }

  while ((odp = read (sck, bufor, BUFSIZE)) > 0)
    write (1, bufor, odp);
  close (sck);

  exit (EXIT_SUCCESS);

}

Client::~Client() {
  printf("client destroyed...\n");
}

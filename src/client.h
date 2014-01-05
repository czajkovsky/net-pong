#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {

public:
  Client(char* server, int service_port);
  ~Client();

};


#endif


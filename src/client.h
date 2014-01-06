#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "IThread.h"
#include "SharedMemory.h"

class Client : public IThread {

public:
  Client(char* server, int service_port, SharedMemory&);
  ~Client();

private:
  virtual void* start_routine();
  int service_port;
  char* service_address;
  SharedMemory& sharedMemory;

};


#endif


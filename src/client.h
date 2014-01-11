#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "IThread.h"
#include "SharedMemory.h"

class Client : public IThread {

public:
  Client(char* server, short service_port, SharedMemory&);
  ~Client();

private:
  virtual void* start_routine();
  short service_port;
  char* service_address;
  SharedMemory& sharedMemory;

};


#endif


#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "IThread.h"
#include "sharedMemory.h"

class Server : public IThread {

public:
  Server(int service_port, SharedMemory&);
  ~Server();

private:
  virtual void* start_routine();
  int service_port;
  SharedMemory& sharedMemory;

};


#endif


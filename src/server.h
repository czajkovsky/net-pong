#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "IThread.h"

class Server : public IThread {

public:
  Server(int service_port);
  ~Server();

private:
  virtual void* start_routine();
  int service_port;

};


#endif


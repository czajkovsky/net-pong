#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include "IThread.h"
#include "SharedMemory.h"

class GameEngine : public IThread {

public:
  GameEngine(SharedMemory&);
  ~GameEngine();

private:
  virtual void* start_routine();
  SharedMemory& sharedMemory;

};


#endif


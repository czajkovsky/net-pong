#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "Mutex.h"
#include "Ball.h"

class SharedMemory {

public:
  SharedMemory();
  bool gameStatus();
  void startGame();

  void getBallPosition(int& x, int& y) const;
  void setBallPosition(int x, int y);

private:
  bool started;
  mutable Mutex mutex;
  Ball ball;

};

#endif // SHARED_MEMORY_H

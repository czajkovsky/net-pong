#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "Mutex.h"
#include "Ball.h"
#include "Player.h"

class SharedMemory {

public:
  SharedMemory();
  bool gameStatus();
  void startGame();
  void endGame();

  void getBallPosition(int& x, int& y) const;
  void setBallPosition(int x, int y);

  void getPlayerPosition(int player, int& x) const;
  void setPlayerPosition(int player, int x);

  void getCurrentState(Ball&, Player&, Player&) const;
  void setCurrentState(const Ball&, const Player&, const Player&);

private:
  bool started;
  mutable Mutex mutex;
  Ball ball;
  Player players[2]; // 0 - server, 1 - client

};

#endif // SHARED_MEMORY_H

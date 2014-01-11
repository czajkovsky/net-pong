#include "SharedMemory.h"
#include <cassert>
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

SharedMemory::SharedMemory() {
  mutex.lock();
  this->started = false;
  mutex.unlock();
}

bool SharedMemory::gameStatus() {
  int started;

  mutex.lock();
  started = this->started;
  mutex.unlock();

  return started;
}

void SharedMemory::startGame() {
  mutex.lock();
  this->started = true;
  mutex.unlock();
}

void SharedMemory::getBallPosition(int& x, int& y) const {
  mutex.lock();
  this->ball.getPosition(x, y);
  mutex.unlock();
}

void SharedMemory::setBallPosition(int x, int y) {
  mutex.lock();
  this->ball.setPosition(x, y);
  mutex.unlock();
}

void SharedMemory::getPlayerPosition(int player, int& x) const {
  mutex.lock();
  this->players[player].getPosition(x);
  mutex.unlock();
}

void SharedMemory::setPlayerPosition(int player, int x) {
  mutex.lock();
  this->players[player].setPosition(x);
  mutex.unlock();
}

void SharedMemory::setCurrentState(const Ball& b, const Player& p0, const Player& p1) {
  mutex.lock();
  ball = b;
  players[0] = p0;
  players[1] = p1;
  mutex.unlock();
}

void SharedMemory::getCurrentState(Ball& b, Player& p0, Player& p1) const {
  mutex.lock();
  b = ball;
  p0 = players[0];
  p1 = players[1];
  mutex.unlock();
}

#include "sharedMemory.h"
#include <cassert>
#include <iostream>

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

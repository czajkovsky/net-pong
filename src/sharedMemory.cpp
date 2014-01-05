#include "sharedMemory.h"
#include <cassert>
#include <iostream>

SharedMemory::SharedMemory() {
  this->started = false;
}

bool SharedMemory::gameStatus() {
  return this->started;
}

void SharedMemory::startGame() {
  this->started = true;
}

#include "sharedMemory.h"
#include <cassert>
#include <iostream>

using namespace common;

SharedMemory::SharedMemory() {
  this->started = false;
}

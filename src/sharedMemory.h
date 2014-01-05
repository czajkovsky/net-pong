#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "Mutex.h"

class SharedMemory
{
public:
  SharedMemory();

private:
  bool started;
  mutable Mutex mutex;

};

}

#endif // SHARED_MEMORY_H

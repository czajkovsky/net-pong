#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
public:
  Mutex();
  void lock();
  void unlock();
  ~Mutex();

private:
  pthread_mutex_t mutex;
};

#endif // MUTEX_H

#include "Mutex.h"
#include <pthread.h>
#include <cstdio>

Mutex::Mutex() {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutex_init(&mutex, &attr);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
  pthread_mutex_lock(&mutex);
}

void Mutex::unlock() {
  pthread_mutex_unlock(&mutex);
}

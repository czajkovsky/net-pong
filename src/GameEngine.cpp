#include <iostream>
#include <unistd.h>

#include "GameEngine.h"
#include "SharedMemory.h"


using namespace std;

GameEngine::GameEngine(SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
}

void* GameEngine::start_routine() {

  while(1) {
    cout << "game engine started...\n";
    sleep(300);
  }
}

GameEngine::~GameEngine() {
  printf("server destroyed...\n");
}

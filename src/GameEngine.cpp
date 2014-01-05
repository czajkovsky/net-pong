#include <iostream>
#include <unistd.h>
#include <Box2D/Box2d.h>
#include "GameEngine.h"
#include "SharedMemory.h"


using namespace std;

GameEngine::GameEngine(SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
}

void* GameEngine::start_routine() {


  int positionX, positionY;
  sharedMemory.getBallPosition(positionX, positionY);
  sharedMemory.setBallPosition(positionX, positionY);

}

GameEngine::~GameEngine() {
}

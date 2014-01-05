#include <iostream>
#include <vector>
#include <string>
#include "app.h"
#include <Box2D/Box2d.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "dimensions.h"
#include "GameEngine.h"
#include "SharedMemory.h"

using namespace std;
using namespace sf;

#define SERVER_MODE 1

void start(SharedMemory& sharedMemory);

int main () {

  int mode = -1;
  short port = 3003;

  scanf("%d", &mode);

  Client *client = NULL;

  SharedMemory sharedMemory;

  if(mode == SERVER_MODE) {

    Server server(port, sharedMemory);
    server.run();
    // while(!sharedMemory.gameStatus());

    GameEngine gameEngine(sharedMemory);
    gameEngine.run();

    start(sharedMemory);

  }
  else {
    client = new Client("127.0.0.1", port);

  }

  return 0;
}

void start(SharedMemory& sharedMemory) {

  // sf::RenderWindow* window;

  // window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), "Pong!");

  sf::Window window(sf::VideoMode(windowWidth, windowHeight), "Pong");

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

  }
}

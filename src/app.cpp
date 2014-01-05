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

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
  window.setVerticalSyncEnabled(true);

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // left key is pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // right key is pressed
    }

    window.clear(sf::Color::White);

    int positionX = windowWidth / 2;
    int positionY = windowHeight - 60;

    sf::RectangleShape bottomPlayer(sf::Vector2f(platformWidth, platformHeight));
    bottomPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
    bottomPlayer.setFillColor(sf::Color::Red);
    window.draw(bottomPlayer);

    // draw borders

    //top
    sf::RectangleShape topBorder(sf::Vector2f(windowWidth - 2 * borderMargin, borderSize));
    topBorder.setPosition(borderMargin, borderMargin);
    topBorder.setFillColor(sf::Color(208, 208, 208));
    window.draw(topBorder);

    //left
    sf::RectangleShape leftBorder(sf::Vector2f(borderSize, windowHeight - 2 * borderMargin));
    leftBorder.setPosition(borderMargin, borderMargin);
    leftBorder.setFillColor(sf::Color(208, 208, 208));
    window.draw(leftBorder);

    //right
    sf::RectangleShape rightBorder(sf::Vector2f(borderSize, windowHeight - 2 * borderMargin));
    rightBorder.setPosition(windowWidth - borderMargin, borderMargin);
    rightBorder.setFillColor(sf::Color(208, 208, 208));
    window.draw(rightBorder);

    //bottom
    sf::RectangleShape bottomBorder(sf::Vector2f(windowWidth - 2 * borderMargin, borderSize));
    bottomBorder.setPosition(borderMargin, windowHeight - borderMargin);
    bottomBorder.setFillColor(sf::Color(208, 208, 208));
    window.draw(bottomBorder);

    window.display();

  }
}

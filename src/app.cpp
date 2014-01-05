#include <iostream>
#include <vector>
#include <string>
#include "app.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "dimensions.h"
#include "GameEngine.h"
#include "SharedMemory.h"

using namespace std;
using namespace sf;

#define SERVER_MODE 1

int app_mode;

void start(SharedMemory& sharedMemory);

int main () {

  int mode = -1;
  short port = 3003;

  scanf("%d", &mode);

  Client *client = NULL;

  SharedMemory sharedMemory;

  if(mode == SERVER_MODE) {

    app_mode = 0;

    Server server(port, sharedMemory);
    server.run();
    // while(!sharedMemory.gameStatus());

    GameEngine gameEngine(sharedMemory);
    gameEngine.run();

    start(sharedMemory);

  }
  else {

    app_mode = 1;

    client = new Client("127.0.0.1", port);

  }

  return 0;
}

void start(SharedMemory& sharedMemory) {

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  int positionX, positionY;

  sharedMemory.setBallPosition(windowWidth / 2, windowHeight / 2);
  sharedMemory.setPlayerPosition(app_mode, 50);

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  sharedMemory.setPlayerPosition(app_mode, windowWidth / 2);
  sharedMemory.setPlayerPosition((app_mode+1)%2, windowWidth / 2);



  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    sharedMemory.getPlayerPosition(app_mode, positionX);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // left key is pressed
      positionX-=7;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // right key is pressed
      positionX+=7;
    }

    positionX = max(borderMargin + platformWidth / 2, positionX);
    positionX = min(windowWidth - borderMargin - platformWidth / 2, positionX);

    sharedMemory.setPlayerPosition(app_mode, positionX);

    window.clear(sf::Color::White);


    // bottom player

    positionY = windowHeight -60;

    sf::RectangleShape bottomPlayer(sf::Vector2f(platformWidth, platformHeight));
    bottomPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
    bottomPlayer.setFillColor(sf::Color(240, 79, 0));
    window.draw(bottomPlayer);

    // top player
    positionX = windowWidth / 2;
    positionY = 60;

    sf::RectangleShape topPlayer(sf::Vector2f(platformWidth, platformHeight));
    topPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
    topPlayer.setFillColor(sf::Color(240, 79, 0));
    window.draw(topPlayer);

    // draw ball

    sharedMemory.getBallPosition(positionX, positionY);

    sf::CircleShape ball(circleRadius);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(positionX - circleRadius, positionY - circleRadius);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color(0, 118, 207));
    window.draw(ball);

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

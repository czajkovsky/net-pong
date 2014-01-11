#include <iostream>
#include <vector>
#include <string>
#include "app.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "dimensions.h"
#include "GameEngine.h"
#include "SharedMemory.h"
#include "Ball.h"
#include "Player.h"

using namespace std;
using namespace sf;

#define SERVER_MODE 1

int app_mode;

void start(SharedMemory& sharedMemory);

int main () {

  int mode = -1;
  short port = 3008;

  scanf("%d", &mode);

  SharedMemory sharedMemory;

  if(mode == SERVER_MODE) {

    app_mode = 0;

    Server server(port, sharedMemory);
    server.run();
    while(!sharedMemory.gameStatus());

    GameEngine gameEngine(sharedMemory);
    gameEngine.run();

    start(sharedMemory);

  }
  else {

    app_mode = 1;

    Client client("127.0.0.1", port, sharedMemory);
    client.run();

    while(!sharedMemory.gameStatus());

    start(sharedMemory);

  }

  return 0;
}

void start(SharedMemory& sharedMemory) {

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  int positionX, positionY;

  Player players[2];
  Ball ball;

  sharedMemory.setBallPosition(windowWidth / 2, windowHeight / 2);

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  sharedMemory.setPlayerPosition(app_mode, windowWidth / 2);
  sharedMemory.setPlayerPosition((app_mode+1)%2, windowWidth / 2);

  sf::Event event;
  bool focus = false;

  while (window.isOpen()) {

    sharedMemory.getPlayerPosition(app_mode, positionX);

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::GainedFocus) focus = true;
      if (event.type == sf::Event::LostFocus) focus = false;
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) window.close();
      }
    }

    if (focus) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) positionX-=7;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) positionX+=7;
    }

    sharedMemory.getCurrentState(ball, players[0], players[1]);

    positionX = max(borderMargin + platformWidth / 2, positionX);
    positionX = min(windowWidth - borderMargin - platformWidth / 2, positionX);

    sharedMemory.setPlayerPosition(app_mode, positionX);

    window.clear(sf::Color::White);

    // bottom player

    positionY = windowHeight -60;
    players[app_mode].getPosition(positionX);


    sf::RectangleShape bottomPlayer(sf::Vector2f(platformWidth, platformHeight));
    bottomPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
    bottomPlayer.setFillColor(sf::Color(240, 79, 0));
    window.draw(bottomPlayer);

    // top player
    players[(app_mode+1)%2].getPosition(positionX);
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

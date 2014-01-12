#include <iostream>
#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "app.h"
#include "dimensions.h"
#include "GameEngine.h"
#include "SharedMemory.h"
#include "Ball.h"
#include "Player.h"

using namespace std;
using namespace sf;

#define SERVER_MODE 0
#define CLIENT_MODE 1

int app_mode;
short port = 4000;
char server_address[50] = "127.0.0.1";
bool launching = true;
bool defaults = false;

void start(SharedMemory& sharedMemory);
int process_input(int argc, char* argv[]);

int main(int argc, char* argv[]) {

  if (process_input(argc, argv) < 0) return -1;

  SharedMemory sharedMemory;

  if(app_mode == SERVER_MODE) {

    Server server(port, sharedMemory);
    server.run();

    while(!sharedMemory.gameStatus() && !sharedMemory.forcedToQuit());

    if(!sharedMemory.forcedToQuit()) {
      GameEngine gameEngine(sharedMemory);
      gameEngine.run();
      start(sharedMemory);
    }

  }
  else {

    Client client(server_address, port, sharedMemory);
    client.run();

    while(!sharedMemory.gameStatus() && !sharedMemory.forcedToQuit());

    if(!sharedMemory.forcedToQuit()) {
      start(sharedMemory);
    }

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

  sharedMemory.setPlayerPosition(0, windowWidth / 2);
  sharedMemory.setPlayerPosition(1, windowWidth / 2);

  sf::Event event;
  bool focus = false;

  while (window.isOpen()) {

    sharedMemory.getPlayerPosition(app_mode, positionX);

    if(!sharedMemory.gameStatus()) {
      window.close();
    }

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        sharedMemory.endGame();
        window.close();
      }
      if (event.type == sf::Event::GainedFocus) focus = true;
      if (event.type == sf::Event::LostFocus) focus = false;
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          sharedMemory.endGame();
          window.close();
        }
      }
    }

    if (focus) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) positionX -= 7;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) positionX += 7;
    }

    positionX = max(borderMargin + platformWidth / 2, positionX);
    positionX = min(windowWidth - borderMargin - platformWidth / 2, positionX);

    sharedMemory.setPlayerPosition(app_mode, positionX);
    window.clear(sf::Color::White);

    sharedMemory.getCurrentState(ball, players[0], players[1]);

    // bottom player (server)
    positionY = windowHeight -60;
    players[0].getPosition(positionX);

    sf::RectangleShape bottomPlayer(sf::Vector2f(platformWidth, platformHeight));
    bottomPlayer.setPosition(positionX - platformWidth/2, positionY - platformHeight/2);
    bottomPlayer.setFillColor(sf::Color(240, 79, 0));
    window.draw(bottomPlayer);


    // top player (client)
    players[1].getPosition(positionX);
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

int process_input(int argc, char* argv[]) {
  if (argc < 2) launching = false;
  else {
    if (strcmp(argv[1], "-s") == 0) {
      app_mode = SERVER_MODE;
      if (argc == 3) port = atoi(argv[2]);
      else if (argc > 3) launching = false;
      else defaults = true;
    }
    else if (strcmp(argv[1], "-c") == 0) {
      app_mode = CLIENT_MODE;
      if (argc == 2) defaults = true;
      else if (argc == 4) {
        cout << argv[2] << "\n";
        strcpy(server_address, argv[2]);
        port = atoi(argv[3]);
      }
      else launching = false;
    }
    else launching = false;
  }

  if (!launching) {
    cout << "Add '-s port' for server or '-c server_address port' for client.\n";
    return -1;
  }
  else {
    if (app_mode == CLIENT_MODE) {
      if (defaults) cout << "Using defaults: " << server_address << ":" << port << "\n";
      else cout << "Using: " << server_address << ":" << port << "\n";
    }
    else {
      if (defaults) cout << "Listening at port [" << port << "] (defualt port)\n";
      else cout << "Listening at [" << port << "]\n";
    }
    return 0;
  }
}

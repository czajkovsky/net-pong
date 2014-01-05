#include <iostream>
#include <vector>
#include <string>
#include "app.h"
#include <Box2D/Box2d.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "dimensions.h"

using namespace std;
using namespace sf;

#define SERVER_MODE 1

void start();

int main () {

  int mode = -1;
  short port = 3003;

  scanf("%d", &mode);

  Server *server = NULL;
  Client *client = NULL;


  SharedMemory *sharedMemory = new SharedMemory();

  if(mode == SERVER_MODE) {
    server = new Server(port, *sharedMemory);
    server->run();
    // while(!sharedMemory->gameStatus());
    start();
  }
  else {
    client = new Client("127.0.0.1", port);
    delete client;
  }

  // destroy connection
  if(mode == SERVER_MODE) delete server;
  else delete client;

  return 0;
}

void start() {

  sf::RenderWindow* window;

  window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), "Pong!");
  printf("game started!!!!\n");

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  const float scaleFactor = 100.0f;

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 0.0f);
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef ceilingBodyDef;
  ceilingBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, windowHeightf/scaleFactor);
  b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
  b2PolygonShape ceilingBox;
  ceilingBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
  ceilingBody->CreateFixture(&ceilingBox, 0.0f);

  b2BodyDef leftBodyDef;
  leftBodyDef.position.Set(0.0f, 0.5f*windowHeightf/scaleFactor);
  b2Body* leftBody = world.CreateBody(&leftBodyDef);
  b2PolygonShape leftSideBox;
  leftSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeight/scaleFactor);
  leftBody->CreateFixture(&leftSideBox, 0.0f);

  b2BodyDef rightBodyDef;
  rightBodyDef.position.Set(windowWidthf/scaleFactor, 0.5f*windowHeightf/scaleFactor);
  b2Body* rightBody = world.CreateBody(&rightBodyDef);
  b2PolygonShape rightSideBox;
  rightSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeightf/scaleFactor);
  rightBody->CreateFixture(&rightSideBox, 0.0f);

  b2BodyDef ballBodyDef;
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position.Set(0.5f*(windowWidthf-circleRadiusf)/scaleFactor, 2.0/*0.5f*(windowHeightf-circleRadiusf)/scaleFactor*/);
  ballBodyDef.gravityScale = 0.0f;
  b2Body* ballBody = world.CreateBody(&ballBodyDef);
  b2CircleShape ballCircle;
  ballCircle.m_radius = circleRadiusf/scaleFactor;
  b2FixtureDef ballFixtureDef;
  ballFixtureDef.shape = &ballCircle;
  ballFixtureDef.density = 1.0f;
  ballFixtureDef.friction = 0.3f;
  ballFixtureDef.restitution = 1.0f;
  ballBody->CreateFixture(&ballFixtureDef);
  srand(time(0));
  double vx = (double)rand()/(double)RAND_MAX * 2.0 - 1.0;
  std::cout << vx << std::endl;
  b2Vec2 vvv(vx, 3.5f);
  ballBody->SetLinearVelocity(vvv);

  b2BodyDef bottomPlayerBodyDef;
  bottomPlayerBodyDef.type = b2_kinematicBody;
  bottomPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, windowHeightf/scaleFactor - 0.9f);
  b2Body* bottomPlayerBody = world.CreateBody(&bottomPlayerBodyDef);
  b2PolygonShape bottomPlayerPolygon;
  bottomPlayerPolygon.SetAsBox(0.5f*platformWidthf/scaleFactor, 0.5f*platformHeightf/scaleFactor);
  b2FixtureDef bottomPlayerFixtureDef;
  bottomPlayerFixtureDef.shape = &bottomPlayerPolygon;
  bottomPlayerFixtureDef.density = 1.0f;
  bottomPlayerFixtureDef.friction = 0.2f;
  bottomPlayerBody->CreateFixture(&bottomPlayerFixtureDef);

  b2BodyDef topPlayerBodyDef;
  topPlayerBodyDef.type = b2_kinematicBody;
  topPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 0.9f);
  b2Body* topPlayerBody = world.CreateBody(&topPlayerBodyDef);
  b2PolygonShape topPlayerPolygon;
  topPlayerPolygon.SetAsBox(0.5*platformWidthf/scaleFactor, 0.5f*platformHeight/scaleFactor);
  b2FixtureDef topPlayerFixtureDef;
  topPlayerFixtureDef.shape = &topPlayerPolygon;
  topPlayerFixtureDef.density = 1.0f;
  topPlayerFixtureDef.friction = 0.2f;
  topPlayerBody->CreateFixture(&topPlayerFixtureDef);

  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  while(true) {
    cout << "dupa\n";
  }

}

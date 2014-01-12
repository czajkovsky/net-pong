#include <iostream>
#include <unistd.h>
#include <Box2D/Box2d.h>
#include "GameEngine.h"
#include "SharedMemory.h"
#include "dimensions.h"


using namespace std;

GameEngine::GameEngine(SharedMemory& sharedMemory) : sharedMemory(sharedMemory) {
}

void* GameEngine::start_routine() {

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  const float scaleFactor = 100.0f;

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 0.0f + borderMarginf/scaleFactor);
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef ceilingBodyDef;
  ceilingBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, windowHeightf/scaleFactor - borderMarginf/scaleFactor);
  b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
  b2PolygonShape ceilingBox;
  ceilingBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
  ceilingBody->CreateFixture(&ceilingBox, 0.0f);

  b2BodyDef leftBodyDef;
  leftBodyDef.position.Set(0.0f + borderMarginf/scaleFactor, 0.5f*windowHeightf/scaleFactor);
  b2Body* leftBody = world.CreateBody(&leftBodyDef);
  b2PolygonShape leftSideBox;
  leftSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeight/scaleFactor);
  leftBody->CreateFixture(&leftSideBox, 0.0f);

  b2BodyDef rightBodyDef;
  rightBodyDef.position.Set(windowWidthf/scaleFactor - borderMarginf/scaleFactor, 0.5f*windowHeightf/scaleFactor);
  b2Body* rightBody = world.CreateBody(&rightBodyDef);
  b2PolygonShape rightSideBox;
  rightSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeightf/scaleFactor);
  rightBody->CreateFixture(&rightSideBox, 0.0f);

  b2BodyDef ballBodyDef;
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position.Set(0.5f*(windowWidthf-circleRadiusf)/scaleFactor, 2.0);
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
  b2Vec2 vvv(vx, 3.5f);
  ballBody->SetLinearVelocity(vvv);

  b2BodyDef bottomPlayerBodyDef;
  bottomPlayerBodyDef.type = b2_kinematicBody;
  bottomPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, (windowHeightf-60.0f)/scaleFactor);
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
  topPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 60.0f/scaleFactor);
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

  int posX;

  while(true) {

    world.Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 bottomPlayerPosition = bottomPlayerBody->GetPosition();
    sharedMemory.getPlayerPosition(0, posX);
    b2Vec2 bottomPlayerLinearVelocity(30.0f*(float(posX) / scaleFactor - bottomPlayerPosition.x), 0.0f);
    bottomPlayerBody->SetLinearVelocity(bottomPlayerLinearVelocity);

    b2Vec2 topPlayerPosition = topPlayerBody->GetPosition();
    sharedMemory.getPlayerPosition(1, posX);
    b2Vec2 topPlayerLinearVelocity(30.0f*(float(posX) / scaleFactor - topPlayerPosition.x), 0.0f);
    topPlayerBody->SetLinearVelocity(topPlayerLinearVelocity);

    if (true) {
      for (b2ContactEdge* ce = ballBody->GetContactList(); ce; ce = ce->next) {
        b2Contact* c = ce->contact;
        if (c->GetFixtureA()->GetBody() == groundBody) {
          // TO-DO add point for client
          b2Vec2 windowCenter(0.5f*(windowWidthf-circleRadiusf)/scaleFactor, 2.0f);
          ballBody->SetTransform(windowCenter, 0.0f);
          double vx = (double)rand()/(double)RAND_MAX * 2.0 - 1.0;
          b2Vec2 vvv(vx, 3.5f);
          ballBody->SetLinearVelocity(vvv);
        }
        if (c->GetFixtureA()->GetBody() == ceilingBody) {
          // TO-DO add point for server
          b2Vec2 windowCenter(0.5f*(windowWidthf-circleRadiusf)/scaleFactor, windowHeightf/scaleFactor-2.0f);
          ballBody->SetTransform(windowCenter, 0.0f);
          double vx = (double)rand()/(double)RAND_MAX * 2.0 - 1.0;
          b2Vec2 vvv(vx, -3.5f);
          ballBody->SetLinearVelocity(vvv);
        }
      }
    }

    b2Vec2 vcx = ballBody->GetLinearVelocity();

    const float minThrV = 3.5f;
    if (vcx.y < minThrV && vcx.y > -minThrV) {
      if (vcx.y >= 0.0f) vcx.y = minThrV;
      else vcx.y = -minThrV;
      ballBody->SetLinearVelocity(vcx);
    }

    const float maxThrV = 10.0f;
    if (vcx.x > maxThrV || vcx.x < -maxThrV) {
      if (vcx.x >= 0.0f) vcx.x = maxThrV;
      else vcx.x = -maxThrV;
      ballBody->SetLinearVelocity(vcx);
    }

    if (vcx.y > maxThrV || vcx.y < -maxThrV) {
      if (vcx.y >= 0.0f) vcx.y = maxThrV;
      else vcx.y = -maxThrV;
      ballBody->SetLinearVelocity(vcx);
    }

    b2Vec2 ballPosition = ballBody->GetPosition();
    sharedMemory.setBallPosition(ballPosition.x * scaleFactor, ballPosition.y * scaleFactor);

    usleep(static_cast<int>(1000000.0/60.0));

  }
}

GameEngine::~GameEngine() {
}

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
  std::cout << vx << std::endl;
  b2Vec2 vvv(vx, 3.5f);
  ballBody->SetLinearVelocity(vvv);

  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  while(true) {

    world.Step(timeStep, velocityIterations, positionIterations);

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

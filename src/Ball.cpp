#include "Ball.h"

Ball::Ball() {
}

void Ball::getPosition(int& x, int& y) const {
  x = this->x;
  y = this->y;
}

void Ball::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

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

void Ball::send(unsigned char* buf, int startPos) const {

  buf[startPos + 0] = ((unsigned char*)&x)[0];
  buf[startPos + 1] = ((unsigned char*)&x)[1];
  buf[startPos + 2] = ((unsigned char*)&x)[2];
  buf[startPos + 3] = ((unsigned char*)&x)[3];
  buf[startPos + 4] = ((unsigned char*)&y)[0];
  buf[startPos + 5] = ((unsigned char*)&y)[1];
  buf[startPos + 6] = ((unsigned char*)&y)[2];
  buf[startPos + 7] = ((unsigned char*)&y)[3];
}

void Ball::receive(unsigned char* buf, int startPos) {

  ((unsigned char*)&x)[0] = buf[startPos + 0];
  ((unsigned char*)&x)[1] = buf[startPos + 1];
  ((unsigned char*)&x)[2] = buf[startPos + 2];
  ((unsigned char*)&x)[3] = buf[startPos + 3];
  ((unsigned char*)&y)[0] = buf[startPos + 4];
  ((unsigned char*)&y)[1] = buf[startPos + 5];
  ((unsigned char*)&y)[2] = buf[startPos + 6];
  ((unsigned char*)&y)[3] = buf[startPos + 7];
}

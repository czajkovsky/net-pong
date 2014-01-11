#include "Player.h"
#include <iostream>

Player::Player() {
}

void Player::getPosition(int& x) const {
  x = this->x;
}

void Player::setPosition(int x) {
  this->x = x;
}

void Player::send(unsigned char* buf, int startPos) const
{
  buf[startPos + 0] = ((unsigned char*)&x)[0];
  buf[startPos + 1] = ((unsigned char*)&x)[1];
  buf[startPos + 2] = ((unsigned char*)&x)[2];
  buf[startPos + 3] = ((unsigned char*)&x)[3];
}

void Player::receive(unsigned char* buf, int startPos)
{
  ((unsigned char*)&x)[0] = buf[startPos + 0];
  ((unsigned char*)&x)[1] = buf[startPos + 1];
  ((unsigned char*)&x)[2] = buf[startPos + 2];
  ((unsigned char*)&x)[3] = buf[startPos + 3];
}

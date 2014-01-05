#include "Player.h"

Player::Player() {
}

void Player::getPosition(int& x) const {
  x = this->x;
}

void Player::setPosition(int x) {
  this->x = x;
}

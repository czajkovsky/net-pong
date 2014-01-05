#ifndef PLAYER_H
#define PLAYER_H

class Player {

public:
  Player();
  void getPosition(int& x) const;
  void setPosition(int x);

private:
  int x;

};

#endif

#ifndef PLAYER_H
#define PLAYER_H

class Player {

public:
  Player();
  void getPosition(int& x) const;
  void setPosition(int x);

  virtual void send(unsigned char*, int startPos) const;
  virtual void receive(unsigned char*, int startPos);

private:
  int x;

};

#endif

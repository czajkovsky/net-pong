#ifndef BALL_H
#define BALL_H

class Ball {

public:
  Ball();
  void getPosition(int& x, int& y) const;
  void setPosition(int x, int y);

  virtual void send(unsigned char*, int startPos) const;
  virtual void receive(unsigned char*, int startPos);

private:
  int x, y;

};

#endif

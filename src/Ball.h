#ifndef BALL_H
#define BALL_H

class Ball {

public:
  Ball();
  void getPosition(int& x, int& y) const;
  void setPosition(int x, int y);

private:
  int x, y;

};

#endif

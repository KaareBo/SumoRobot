#ifndef Sumo_h
#define Sumo_h

#include "Arduino.h"

class Sumo{
public:
  Sumo(int speedA, int dirA1, int dirA2, int speedB, int dirB1, int dirB2);
  void forwards(int speed);
  void backwards(int speed);
  void right(int speed, int time);
  void left(int speed, int time);
  void beyblade();
  void stop();

private:
  int _speedA;
  int _dirA1;
  int _dirA2;
  int _speedB;
  int _dirB1;
  int _dirB2;
};

#endif

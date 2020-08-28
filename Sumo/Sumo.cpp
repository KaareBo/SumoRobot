//  Sumo.cpp - Bibliotek for kontroll av sumo robot med motorkontroller typ L298N/L293D
//  Skrevet av Torbjørn Gorsetbakk 2020/2021

#include "Arduino.h"
#include "Sumo.h"
Sumo::Sumo(int speedA, int dirA1, int dirA2, int speedB, int dirB1, int dirB2){
  pinMode(speedA, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(speedB, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);

  _speedA = speedA;
  _dirA1 = dirA1;
  _dirA2 = dirA2;
  _speedB = speedB;
  _dirB1 = dirB1;
  _dirB2 = dirB2;
}

void Sumo::forwards(int speed){
  //Kontroll av motor A
  analogWrite(_speedA, speed);
  digitalWrite(_dirA1, HIGH);
  digitalWrite(_dirA2, LOW);

  //Kontroll av motor B
  analogWrite(_speedB, speed);
  digitalWrite(_dirB1, LOW);
  digitalWrite(_dirB2, HIGH);
}

void Sumo::backwards(int speed){
  //Kontroll av motor A
  analogWrite(_speedA, speed);
  digitalWrite(_dirA1, LOW);
  digitalWrite(_dirA2, HIGH);

  //Kontroll av motor B
  analogWrite(_speedB, speed);
  digitalWrite(_dirB1, HIGH);
  digitalWrite(_dirB2, LOW);
}

void Sumo::right(int speed, int time){
  //Kontroll av motor A
  analogWrite(_speedA, speed);
  digitalWrite(_dirA1, HIGH);
  digitalWrite(_dirA2, LOW);

  //Kontroll av motor B
  analogWrite(_speedB, speed);
  digitalWrite(_dirB1, HIGH);
  digitalWrite(_dirB2, LOW);

  delay(time);

  Sumo:stop();
}


void Sumo::left(int speed, int time){
  //Kontroll av motor A
  analogWrite(_speedA, speed);
  digitalWrite(_dirA1, LOW);
  digitalWrite(_dirA2, HIGH);

  //Kontroll av motor B
  analogWrite(_speedB, speed);
  digitalWrite(_dirB1, LOW);
  digitalWrite(_dirB2, HIGH);

  delay(time);

  Sumo::stop();
}


void Sumo::stop(){
  //Kontroll av motor A
  analogWrite(_speedA, 0);

  //Kontroll av motor B
  analogWrite(_speedB, 0);
}

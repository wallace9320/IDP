#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* m1 = AFMS.getMotor(1);
Adafruit_DCMotor* m2 = AFMS.getMotor(2);
Adafruit_DCMotor* m3 = AFMS.getMotor(3);
Adafruit_DCMotor* m4 = AFMS.getMotor(4);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  m1->setSpeed(0);
  m2->setSpeed(50);
  m3->setSpeed(150);
  m4->setSpeed(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  m1->run(FORWARD);
  m2->run(FORWARD);
  m3->run(FORWARD);
  m4->run(FORWARD);
}

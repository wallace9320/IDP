#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* ml = AFMS.getMotor(2);
Adafruit_DCMotor* mr = AFMS.getMotor(1);
Adafruit_DCMotor* m3 = AFMS.getMotor(3);
Adafruit_DCMotor* m4 = AFMS.getMotor(4);
unsigned long timeStart;
const int normalSpeed = 200;
const int innerTurnSpeed = 100;

void setup() {
  // put your setup code here, to run once:
  timeStart = millis();
  Serial.begin(9600);
  AFMS.begin();
  ml->setSpeed(255);
  mr->setSpeed(255);
  ml->run(FORWARD);
  mr->run(FORWARD);
}

void loop() {

  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(1000);
  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(2000);
  //dropping sequence
  ml->run(BACKWARD);
  mr->run(BACKWARD);
  delay(2000);
  mr->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(1000);
  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);
  mr->run(FORWARD);
  // put your main code here, to run repeatedly:
  // if (millis() - timeStart > 1000) {
  //   m1->setSpeed(100);
  //   m2->setSpeed(100);
  // }


}

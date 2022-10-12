#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* m1 = AFMS.getMotor(1);
Adafruit_DCMotor* m2 = AFMS.getMotor(2);
Adafruit_DCMotor* m3 = AFMS.getMotor(3);
Adafruit_DCMotor* m4 = AFMS.getMotor(4);
unsigned long timeStart;


void setup() {
  // put your setup code here, to run once:
  timeStart = millis();
  Serial.begin(9600);
  AFMS.begin();
  m1->setSpeed(100);
  m2->setSpeed(200);
}

void loop() {
  m1->run(BACKWARD);
  m2->run(FORWARD);
  // put your main code here, to run repeatedly:
  // if (millis() - timeStart > 1000) {
  //   m1->setSpeed(100);
  //   m2->setSpeed(100);
  // }


}

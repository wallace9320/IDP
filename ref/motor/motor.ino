#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* ml = AFMS.getMotor(1);
Adafruit_DCMotor* mr = AFMS.getMotor(2);

#define BLACK 0
#define WHITE 1
unsigned long timeStart;
const int normalSpeed = 150;
const int ot = 120;
const int it = 30;
int leftLSReading = 0;
int rightLSReading = 0;
const int leftLSPin = 0;
const int rightLSPin = 1;
const int rrrPin = 2;
int mlSpeed = normalSpeed;
int mrSpeed = noramlSpeed;

void setNormalSpeed() {
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
}

void followLine() {
  leftLSReading = digitalRead(leftLSPin);
  rightLSReading = digitalRead(rightLSPin);
  rrrReading = digitalRead(rrrPin);
  Serial.print(leftLSReading);
  Serial.print(" <-L  R-> ");
  Serial.println(rightLSReading);
  if (leftLSReading == WHITE && rightLSReading == BLACK) {
    if (mlSpeed != ot || mrSpeed != it) {
      ml->setSpeed(ot);
      mr->setSpeed(it);
    }
  }
  else if (leftLSReading == BLACK && rightLSReading == WHITE && rrrReading == BLACK) {
    if (mlSpeed != it || mrSpeed != ot) {
      ml->setSpeed(it);
      mr->setSpeed(ot);
    }
  }  
  else if (mlSpeed != normalSpeed || mrSpeed != normalSpeed) {
    setNormalSpeed();
  }  
}
void setup() {
  // put your setup code here, to run once:
  timeStart = millis();
  Serial.begin(9600);
  AFMS.begin();
  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(rrrPin, INPUT);
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);
  mr->run(FORWARD);
}

void loop() {

  followLine();

  // mr->setSpeed(innerTurnSpeed);
  // mr->run(BACKWARD);
  // delay(1000);
  // mr->setSpeed(normalSpeed);
  // mr->run(FORWARD);
  // delay(2000);
  // //dropping sequence
  // ml->run(BACKWARD);
  // mr->run(BACKWARD);
  // delay(2000);
  // mr->setSpeed(innerTurnSpeed);
  // mr->run(FORWARD);
  // delay(1000);
  // mr->setSpeed(normalSpeed);
  // ml->run(FORWARD);
  // mr->run(FORWARD);
  // put your main code here, to run repeatedly:
  // if (millis() - timeStart > 1000) {
  //   m1->setSpeed(100);
  //   m2->setSpeed(100);
  // }


}

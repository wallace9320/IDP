#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* ml = AFMS.getMotor(1);
Adafruit_DCMotor* mr = AFMS.getMotor(2);

#define BLACK 0
#define WHITE 1
unsigned long timeStart;
const int normalSpeed = 255;
const int ot = 250;
const int it = 200;
int leftLSReading = 0;
int rightLSReading = 0;
int rrrReading = 0;
const int leftLSPin = 0;
const int rightLSPin = 1;
const int rrrPin = 2;
const int lservoPin = 10;
const int rservoPin = 9;
const int trigPin = 7;
const int echoPin = 8;
const int IRPin = A2;
int tunnelLeftClearance = 5;
int mlSpeed = normalSpeed;
int mrSpeed = normalSpeed;

bool holding = true;

Servo lservo;
Servo rservo;

void setNormalSpeed() {
  if (mlSpeed != normalSpeed || mrSpeed != normalSpeed) {
    ml->setSpeed(normalSpeed);
    mr->setSpeed(normalSpeed);
    ml->run(FORWARD);
    mr->run(FORWARD);
    mlSpeed = normalSpeed;
    mrSpeed = normalSpeed;
  }
}

void turnRight() {
  if (mlSpeed != ot || mrSpeed != it) {
    ml->setSpeed(ot);
    mr->setSpeed(it);
    ml->run(FORWARD);
    mr->run(BACKWARD);
    mlSpeed = ot;
    mrSpeed = it;
  }
}

void turnLeft() {
  if (mlSpeed != it || mrSpeed != ot) {
    ml->setSpeed(it);
    mr->setSpeed(ot);
    ml->run(BACKWARD);
    mr->run(FORWARD);
    mlSpeed = it;
    mrSpeed = ot;
  }
}

// process value from US sensor
int readUSSensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void followLine() {
  leftLSReading = digitalRead(leftLSPin);
  rightLSReading = digitalRead(rightLSPin);
  rrrReading = digitalRead(rrrPin);
  // usReading = digitalRead(usPin);
  // Serial.print(leftLSReading);
  // Serial.print(" <-L  R-> ");
  // Serial.print(rightLSReading);
  // Serial.print("       RM-> ");
  // Serial.println(rrrReading);
  // if (millis() - timeStart > 500) {
  //   timeStart = millis();
  //   Serial.print(mlSpeed);
  //   Serial.print(" <-L  R-> ");
  //   Serial.println(mrSpeed);
  // }

  if (leftLSReading == WHITE && rightLSReading == BLACK) turnLeft();
  else if (leftLSReading == BLACK && rightLSReading == WHITE && rrrReading == BLACK) turnRight();
  else setNormalSpeed();
}

void setup() {
  // put your setup code here, to run once:
  timeStart = millis();
  Serial.begin(9600);
  AFMS.begin();
  lservo.attach(lservoPin);
  rservo.attach(rservoPin);
  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(rrrPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);
  mr->run(FORWARD);
  // lservo.write(135.0/270*180);
  // rservo.write(15.0/270*180);  
  // delay(500);
  lservo.write(15.0/270*180);
  rservo.write(135.0/270*180);
}

void tunnelDriving() {
  int leftUSreading = readUSSensor();
  if (leftUSreading < tunnelLeftClearance + 0.5) turnRight();
  else if (leftUSreading > tunnelLeftClearance - 0.5) turnLeft();
  else setNormalSpeed();
}

void loop() {
  if (holding && leftUS.reading(readUSSensor(true)) < 10)
    tunnelDriving();
  else
    followLine();
}

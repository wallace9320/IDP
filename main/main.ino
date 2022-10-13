#include <movingAvg.h>
#include <SharpIR.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Constants
#define BLACK 1
#define WHITE 0
const int normalSpeed = 200;
const int innerTurnSpeed = 100; // Speed of inner wheel when turning
const int slowSpeed = 50;       // Speed when very close to block
const int blockDistance = 5;
const int ceilingThreshold = 10;
const int tunnelLeftClearance = 5;
const int hallThreshold;
const int encoderThreshold;

// pins
const int leftLSPin = 0;
const int rightLSPin = 1;
const int farRightLSPin = 2;
const int frontUSechoPin = 3;
const int frontUStrigPin = 4;
const int leftUSechoPin = 5;
const int leftUStrigPin = 6;
const int buttonPin = 7;
const int redLED = 8;
const int greenLED = 9;
const int IRPin = A2;

// booleans for logic
bool start = true;
bool holding = false;
bool magnet = false;
bool drop = false;
bool button = false;

// time
unsigned long timeStart;
unsigned long timeButton;

int noOfWhiteLines = 0;

// moving averages
movingAvg frontUS(3);
movingAvg leftUS(3);
movingAvg topIR(3);
movingAvg rightMostLine(3);

// sensors
SharpIR topIRSensor = SharpIR(IRPin, 1080);

// motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ml = AFMS.getMotor(2);
Adafruit_DCMotor *mr = AFMS.getMotor(1);

// process value from US sensor
int readUSSensor(bool front = true)
{
  int trigPin = front ? frontUStrigPin : leftUStrigPin;
  int echoPin = front ? frontUSechoPin : leftUSechoPin;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void setup()
{
  // set the normal motor speed
  AFMS.begin();
  setNormalSpeed();
  ml->run(FORWARD);
  mr->run(FORWARD);

  // moving avgs
  frontUS.begin();
  leftUS.begin();
  topIR.begin();
  rightMostLine.begin();

  // pin initialization
  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(farRightLSPin, INPUT);
  pinMode(frontUStrigPin, OUTPUT);
  pinMode(frontUSechoPin, INPUT);
  pinMode(leftUStrigPin, OUTPUT);
  pinMode(leftUSechoPin, INPUT);
  pinMode(buttonPin, INPUT);

  timeButton = millis();
}

void loop()
{
  if (digitalRead(buttonPin) == HIGH && millis() - timeButton > 1000)
  {
    button = !button;
    timeButton = millis();
  }
  if (button)
  {
    // if start is true run starting sequence else run main
    // frontUSQueue.push(frontUS)
    if (start)
      initialMovement(); // in initial, everything is hard coded until enter white line loop
    else if (drop)
      droppingMovement(); // in drop, will do turning, dropping, backing, and change holding bool to false
    else
    {
      // if within 5 cm of block lower speed of motor
      if (frontUS.reading(readUSSensor(true)) < 5)
        setLowerSpeed();
      else
        setNormalSpeed();

      // if within 1 cm of block stop
      // initialize pick up sequence
      // arrest others; run all in one go
      if (frontUS.reading(readUSSensor(true)) < 1 && !holding)
        pickupAll();

      // if in tunnel drive in tunnel else follow line
      if (topIR.reading(topIRSensor.distance()) < ceilingThreshold)
        tunnelDriving();
      else
        followLine();

      // The first condition is only trigger if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
      // The second conditionis if is to make sure it has traveled a certain distance, ie must be somewhere far away,
      // so crossing that white cross won't trigger this
      if (millis() - timeStart > 3000 && rightMostLine.reading(analogRead(farRightLSPin)) == WHITE)
      {
        noOfWhiteLines++;
        // we can add an LED to signal this happened
        timeStart = millis();
      }

      if (holding && (magnet && noOfWhiteLines >= 3 || !magnet && noOfWhiteLines == 1))
        drop = true;

      // DO IT LATER
      // if receive command from user
      // begin parking sequence
    }
  }
}

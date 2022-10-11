#include <movingAvg.h>
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

// moving averages
movingAvg frontUS(3);
movingAvg leftUS(3);
movingAvg topIR(3);
movingAvg rightMostLine(3);

// int sensorMovingAvg = mySensor.reading(analogRead(SENSOR_PIN));

// booleans for logic
bool start = true;
bool holding = false;
bool drop = false;

// motor set up
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ml = AFMS.getMotor(1);
Adafruit_DCMotor *mr = AFMS.getMotor(2);

void setup()
{
  // set the normal motor speed
  AFMS.begin();
  normalSpeed();
  frontUS.begin();
  leftUS.begin();
  topIR.begin();
  rightMostLine.begin();
}

void loop()
{
  // if start is true run starting sequence else run main
  // frontUSQueue.push(frontUS)
  if (start)
    initial(); // in initial, everything is hard coded until enter white line loop
  else if (drop)
    drop(); // in drop, will do turning, dropping, backing, and change holding bool to false
  else
  {
    // if within 5 cm of block lower speed of motor
    if (frontUS.reading(analogRead(FRONT_PIN)) < 5)
      lowerSpeed();
    else
      normalSpeed();

    // if within 1 cm of block stop
    // initialize pick up sequence
    // set encoder reference point
    // arrest others; run all in one go
    if (frontUS.reading(analogRead(FRONT_PIN)) < 1 && !pickup)
      pickupAll();

    // if in tunnel drive in tunnel else follow line
    if (topIR.reading(analogRead(TOP_PIN)) < ceilingThreshold)
      tunnelDriving();
    else
      followLine();

    // The first condition is only trigger if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
    // The second conditionis if is to make sure it has traveled a certain distance, ie must be somewhere far away,
    // so crossing that white cross won't trigger this
    if (millis() - timeStart > 3000 && encoderReading > encoderThreshold && rightMostLine.reading(analogRead(RIGHT_MOST_LINE_PIN)) == WHITE)
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

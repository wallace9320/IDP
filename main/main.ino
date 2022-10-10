#include <cppQueue.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Constants
#define BLACK 1
#define WHITE 0
const int normalSpeed = 200;
const int innerTurnSpeed = 100; //Speed of inner wheel when turning
const int slowSpeed = 50; //Speed when very close to block
const int blockDistance = 5;
const int ceilingThreshold = 10;
const int tunnelLeftClearance = 5;
const int hallThreshold;
const int encoderThreshold;

// Moving average of front sensor
// cppQueue frontUSQueue(sizeof(double), 3, FIFO, overwrite=true);

// booleans for logic
bool start = true;
bool pickup = false;

// motor set up
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* ml = AFMS.getMotor(1);
Adafruit_DCMotor* mr = AFMS.getMotor(2);

void setup() {
  // set the normal motor speed
  AFMS.begin()
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
}

void loop() {
  // if start is true run starting sequence else run main
  // frontUSQueue.push(frontUS)
  if (start) initial();
  else {
    //if within 5 cm of block lower speed of motor
    if (frontUS < 5) lowerSpeed();
    else normalSpeed();

    //if within 1 cm of block stop
      //initialize pick up sequence
      //set encoder reference point
      //arrest others; run all in one go
    if (frontUS < 1 && !pickup) pickupAll();

    //if in tunnel drive in tunnel else follow line
    if (topIR < ceilingThreshold) tunnelDriving();
    else followLine();

    if (encoderReading > encoderThreshold) {
      //if running average then noWhiteLines++
    }

    if (magnet && noWhiteLines >= 3) 
      //initialize turning, dropping, and backing
      drop();
    }
    if (!magnet && noWhiteLines == 1) {
      //initialize turning, dropping, and backing
      drop();
    }


    // DO IT LATER
    //if receive command from user
      //begin parking sequence

  }

}


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define BLACK 1
#define WHITE 0
const int normalSpeed = 200
const int blockDistance = 5
bool start = true


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* ml = AFMS.getMotor(1);
Adafruit_DCMotor* mr = AFMS.getMotor(2);

void setup() {
  // set the normal motor speed
  AFMS.begin()
  ml->setSpeed(200);
  mr->setSpeed(200);
}

void loop() {
  // if start is true run starting sequence else run main
  if (start) initial();
  else {
    //if within 5 cm of block lower speed of motor

    //if within 1 cm of block stop
      //initialize pick up sequence
      //set pickup boolean to true
      //set magnet boolean

    //if in tunnel drive in tunnel else follow line

    //if after exit tunnel begin counting

    //if pickup boolean
      //if magnet boolean
        //within certain encoder count and third white
          //initialize turning, dropping, and backing
      //else
        //within certain encoder count and first white
          //initialize turning, dropping, and backing

    // DO IT LATER
    //if receive command from user
      //begin parking sequence

  }

}


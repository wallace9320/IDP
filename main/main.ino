#include "constant.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Servo lservo;
Servo rservo;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ml = AFMS.getMotor(1);
Adafruit_DCMotor *mr = AFMS.getMotor(2);

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
  AFMS.begin();
  setNormalSpeed();
  ml->run(FORWARD);
  mr->run(FORWARD);

  lservo.attach(lservoPin);
  rservo.attach(rservoPin);
  lservo.write(15.0/270*180);
  rservo.write(135.0/270*180);

  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(farRightLSPin, INPUT);
  pinMode(frontUStrigPin, OUTPUT);
  pinMode(frontUSechoPin, INPUT);
  pinMode(leftUStrigPin, OUTPUT);
  pinMode(leftUSechoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(hallEffectPin, OUTPUT);
  pinMode(runningLED, OUTPUT);  

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
    digitalWrite(runningLED, HIGH);
    // if start is true run starting sequence else run main
    if (start)
      initialMovement(); // in initial, everything is hard coded until enter white line loop
    else
    {
      // if within 5 cm of block lower speed of motor
      if (readUSSensor(true) < 10)
        setLowerSpeed();
      else
        setNormalSpeed();

      // if within 1 cm of block stop, initialize pick up sequence; arrest others; run all in one go
      if ((readUSSensor(true) < 4 || readUSSensor(true) > 980) && !holding)
        pickupAll();

      // if in tunnel drive in tunnel else follow line
      if (holding && readUSSensor(true) < 10)
        tunnelDriving();
      else
        followLine();

      // The first condition is only trigger if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
      // The second conditionis if is to make sure it has traveled a certain distance, ie must be somewhere far away,
      // so crossing that white cross won't trigger this
      if (millis() - pickupTime > 20000 && millis() - timeStart > 3000 && digitalRead(farRightLSPin) == WHITE)
      {
        noOfWhiteLines++;
        // we can add an LED to signal this happened
        timeStart = millis();
      }

      if (holding && (magnet && noOfWhiteLines >= 3 || !magnet && noOfWhiteLines == 1))
        droppingMovement(); // hard coded, run all at once

    }
  }
  else
    digitalWrite(runningLED, LOW);
}

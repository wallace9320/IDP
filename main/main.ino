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
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void setup()
{
  Serial.begin(9600);
  AFMS.begin();
  ml->setSpeed(0);
  mr->setSpeed(0);
  ml->run(FORWARD);
  mr->run(FORWARD);

  lservo.attach(lservoPin);
  rservo.attach(rservoPin);
  lservo.write(150.0/270*180);
  rservo.write(0.0/270*180);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(farRightLSPin, INPUT);
  pinMode(frontUStrigPin, OUTPUT);
  pinMode(frontUSechoPin, INPUT);
  pinMode(leftUStrigPin, OUTPUT);
  pinMode(leftUSechoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(hallEffectPin, INPUT);
  pinMode(runningLED, OUTPUT);  

  timeButton = millis();
  timeLED = millis();

  delay(1000);
} 

void loop()
{
  // button debouncing
  if (digitalRead(buttonPin) == LOW && millis() - timeButton > 1000)
  {
    button = !button;
    timeButton = millis();
  }
  if (button)
  {
    digitalWrite(runningLED, HIGH);
    // if start is true (at the beginningrun starting sequence else run main
    if (start) {
      initialMovement(); // in initial, everything is hard coded until enter white line loop
    }
    else
    { 
      frontUS = readUSSensor(true);
      leftUS = readUSSensor(false);

      // hard coded turn left sequence to go up the ramp
      if (!turn && frontUS < 30)
        hardLeft();
      if (frontUS < 10)
        setLowerSpeed();
      else
        setNormalSpeed();

      // if within 1 cm of block stop, initialize pick up sequence; arrest others; run all in one go
      if ((frontUS < 4 && millis() - timeHard > 15000) && turn && !holding)
        pickupAll();

      followLine();

      // only triggered if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
      if (millis() - timePickUp > 20000 && millis() - timeStart > 3000 && digitalRead(farRightLSPin) == WHITE)
      {
        noOfWhiteLines++;
        timeStart = millis();
      }

      // dropping
      if (holding && (magnet && noOfWhiteLines == 3 || !magnet && noOfWhiteLines == 1))
        droppingMovement();

      // parking
      if (delivered == 1 && (!magnet && noOfWhiteLines == 5 || magnet && noOfWhiteLines == 3)\
       || delivered == 2 && (!magnet && noOfWhiteLines == 1 || magnet && noOfWhiteLines == 3))
        goHome();
    }
  }
  else {
    ml->setSpeed(0);
    mr->setSpeed(0);
    mlSpeed = 0;
    mrSpeed = 0;
    digitalWrite(runningLED, LOW);
  }
}

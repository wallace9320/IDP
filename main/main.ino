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
  // delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
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
  lservo.write(135.0/270*180);
  rservo.write(15.0/270*180);

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
  if (digitalRead(buttonPin) == LOW && millis() - timeButton > 1000)
  {
    button = !button;
    timeButton = millis();
  }
  if (button)
  {
    digitalWrite(runningLED, HIGH);
    // if start is true run starting sequence else run main
    if (start) {
      Serial.println("Start");
      initialMovement(); // in initial, everything is hard coded until enter white line loop
    }
    else
    { 
      frontUS = readUSSensor(true);
      leftUS = readUSSensor(false);
      Serial.print(digitalRead(buttonPin));
      Serial.print("  Hall effect  ");
      Serial.print(analogRead(hallEffectPin));
      Serial.print("  FUS  ");
      Serial.print(frontUS);
      Serial.print("  LUS  ");
      Serial.print(leftUS);
      Serial.print("  holding  ");
      Serial.print(holding);
      Serial.print("  magnet  ");
      Serial.print(magnet);
      Serial.print("  ls  ");
      Serial.print(mlSpeed);
      Serial.print("  rs  ");
      Serial.print(mrSpeed);
      Serial.print("  white  ");
      Serial.println(noOfWhiteLines);


      // Serial.println();
      // if within 5 cm of block lower speed of motor
      if (!turn && frontUS < 30)
        hardLeft();
      if (frontUS < 10)
        setLowerSpeed();
      else
        setNormalSpeed();

      // if within 1 cm of block stop, initialize pick up sequence; arrest others; run all in one go
      if ((frontUS < 4 || frontUS > 2000 && millis() - timeHard > 15000) && !holding)
        pickupAll();


      followLine();

      // SEARCH ALGORITHM
      if (millis() - timeHard > 20000 && turn && delivered == 1 && 20 < leftUS < 50) {
        delay(700);
        ml->setSpeed(innerTurnSpeed);
        ml->run(BACKWARD);
        while (readUSSensor(true) + 5 > leftUS) continue;
        delay(100);
        ml->setSpeed(normalSpeed);
        ml->run(FORWARD);
        while (4 < frontUS < 2000) continue;
        pickupAll();
      }

      // only triggered if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
      if (millis() - timePickUp > 20000 && millis() - timeStart > 3000 && digitalRead(farRightLSPin) == WHITE)
      {
        noOfWhiteLines++;
        timeStart = millis();
      }

      if (holding && (magnet && noOfWhiteLines == 3 || !magnet && noOfWhiteLines == 1))
        droppingMovement();

      // home code
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
    Serial.println("Out");
  }
    

}

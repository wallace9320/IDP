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
    if (millis() - timeLED > 250) {
      timeLED = millis();
      led = !led;
    }
    digitalWrite(runningLED, led);
    // if start is true run starting sequence else run main
    if (start) {
      Serial.println("Start");
      initialMovement(); // in initial, everything is hard coded until enter white line loop
    }
    else
    { 
      frontUS = readUSSensor(true);
      Serial.print(digitalRead(buttonPin));
      Serial.print("  Hall effect  ");
      Serial.print(analogRead(hallEffectPin));
      Serial.print("  US  ");
      Serial.print(frontUS);
      Serial.print("  start  ");
      Serial.print(start);
      Serial.print("  holding  ");
      Serial.print(holding);
      Serial.print("  magnet  ");
      Serial.print(magnet);
      Serial.print("  turn  ");
      Serial.print(turn);
      Serial.println("  white line  ");


      // Serial.println();
      // if within 5 cm of block lower speed of motor
      if (!turn && frontUS < 30)
        hardLeft();
      if (frontUS < 10)
        setLowerSpeed();
      else
        setNormalSpeed();

      // if within 1 cm of block stop, initialize pick up sequence; arrest others; run all in one go
      if (frontUS < 4 && !holding)
        pickupAll();

      // if (holding && readUSSensor(false) < 10)
      //   tunnelDriving();
      
      followLine();

      // only triggered if 3 seconds elapsed since last addition of white line, so same line won't be calculated twice
      if (holding && millis() - timeStart > 3000 && digitalRead(farRightLSPin) == WHITE)
      {
        noOfWhiteLines++;
        timeStart = millis();
      }

      if (holding && (magnet && noOfWhiteLines >= 4 || !magnet && noOfWhiteLines == 2))
        droppingMovement();
    }
  }
  else {
    digitalWrite(runningLED, LOW);
    Serial.println("Out");
  }
    

}

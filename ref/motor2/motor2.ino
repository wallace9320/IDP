#include "constant.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

bool found = false;
Servo lservo;
Servo rservo;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ml = AFMS.getMotor(1);
Adafruit_DCMotor *mr = AFMS.getMotor(2);

int i = 0;

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

void setup() {
  // put your setup code here, to run once:
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

void loop() {
  if (digitalRead(buttonPin) == LOW && millis() - timeButton > 1000)
  {
    button = !button;
    timeButton = millis();
    ml->setSpeed(255);
    mr->setSpeed(255);
  }
  if (button) {
    frontUS = readUSSensor(true);
    leftUS = readUSSensor(false);
    // Serial.print(i);
    Serial.print("     ");
    Serial.print(frontUS);
    Serial.print("     ");
    Serial.println(leftUS);
    // i++;
    if (!found && leftUS < 60) {
      delay(700);
      ml->setSpeed(innerTurnSpeed);
      ml->run(BACKWARD);
      while (readUSSensor(true) + 5 > leftUS){
        Serial.print("     ");
        Serial.print(frontUS);
        Serial.print("     ");
        Serial.println(leftUS);
      }
      delay(100);
      ml->setSpeed(normalSpeed);
      ml->run(FORWARD);
      found = true;
    }
    if ((frontUS < 4 || frontUS > 2000 && millis() - timeHard > 15000) && !holding) {
      Serial.println("set zero");
      ml->setSpeed(0);
      mr->setSpeed(0);
      delay(3000);
    }
  }

}

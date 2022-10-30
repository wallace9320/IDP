// Stop the robot
void stop()
{
  ml->setSpeed(0);
  mr->setSpeed(0);
  mlSpeed = 0;
  mrSpeed = 0;
}

// Set the two booleans
void pickupSetup()
{
  holding = true;
  magnet = (analogRead(hallEffectPin) > 200); // Find better ways to increase reliability, e.g. read 5 values then take average
}

void actualPickup()
{
  lservo.write(15.0 / 270 * 180);
  rservo.write(135.0 / 270 * 180);
  delay(300);
}

void pickupAll()
{
  stop();
  digitalWrite(runningLED, LOW);
  pickupSetup();
  if (magnet)
    digitalWrite(redLED, HIGH);
  else
    digitalWrite(greenLED, HIGH);
  delay(5000);
  if (magnet)
    digitalWrite(redLED, LOW);
  else
    digitalWrite(greenLED, LOW);
  actualPickup();
  digitalWrite(runningLED, HIGH);
  timePickUp = millis();
  noOfWhiteLines = 0;
}

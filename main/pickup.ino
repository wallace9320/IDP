// Stop the robot
void stop() {
  ml->setSpeed(0);
  mr->setSpeed(0);
}

// Set the two booleans
void pickupSetup() {
  holding = true;
  magnet = (hallValue > hallThreshold); // Find better ways to increase reliability, e.g. read 5 values then take average
}

void actualPickup() {
  //pickup mechanism to be decided depending on mechanical team
}

void pickupAll() {
  stop();
  //set encoder reference point
  pickupSetup();
  if (magnet) digitalWrite(RedLED, HIGH);
  else digitalWrite(GreenLED, HIGH);
  delay(5000);
  if (magnet) digitalWrite(RedLED, LOW);
  else digitalWrite(GreenLED, LOW);
  actualPickup();
}
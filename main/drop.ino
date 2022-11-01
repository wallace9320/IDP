void actualDropping() {
  lservo.write(135.0/270*180);
  rservo.write(15.0/270*180);
}

void droppingMovement() {
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  if (magnet) delay(turnTime);
  else delay(turnTime-500);

  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(straightTime);

  actualDropping();

  ml->run(BACKWARD);
  mr->run(BACKWARD);
  delay(straightTime+300); //1000

  ml->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(2000);
  while (digitalRead(rightLSPin) == BLACK) continue;
  // if (magnet) delay(turnTime+300);
  // else delay(turnTime);

  ml->setSpeed(normalSpeed);
  ml->run(FORWARD);

  holding = false;
  // noOfWhiteLines = 0; home code
  turn = false;
  timeStart = millis();
  delivered++;
  noOfWhiteLines = 0;
}

void goHome() {
  delay(1000);
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(turnTime+250);
  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  while (readUSSensor(true) > 4) continue;
  ml->setSpeed(0);
  mr->setSpeed(0);
  button = false;
}
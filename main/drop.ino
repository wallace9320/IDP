void actualDropping() {
  lservo.write(150.0/270*180);
  rservo.write(0.0/270*180);
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
  delay(straightTime+300);

  ml->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  if (magnet) delay(3000);
  else delay(2100);
  while (digitalRead(rightLSPin) == BLACK) continue;

  ml->setSpeed(normalSpeed);
  ml->run(FORWARD);

  holding = false;
  turn = false;
  timeStart = millis();
  delivered++;
  noOfWhiteLines = 0;
}

void goHome() {
  delay(1000);
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(500);
  while (digitalRead(leftLSPin) == BLACK) continue;
  delay(300);
  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(1500);
  while (readUSSensor(true) > 4) continue;
  ml->setSpeed(0);
  mr->setSpeed(0);
  button = false;
  turn = false;
}
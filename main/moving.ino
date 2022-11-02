void setLowerSpeed() {
  if (mlSpeed != slowSpeed || mrSpeed != slowSpeed) {
    ml->setSpeed(slowSpeed);
    mr->setSpeed(slowSpeed);
    ml->run(FORWARD);
    mr->run(FORWARD);
    mlSpeed = slowSpeed;
    mrSpeed = slowSpeed;
  }
}

void setNormalSpeed() {
  if (mlSpeed != normalSpeed || mrSpeed != normalSpeed) {
    ml->setSpeed(normalSpeed);
    mr->setSpeed(normalSpeed);
    ml->run(FORWARD);
    mr->run(FORWARD);
    mlSpeed = normalSpeed;
    mrSpeed = normalSpeed;
  }
}

void turnRight() {
  if (mlSpeed != ot || mrSpeed != it) {
    ml->setSpeed(ot);
    mr->setSpeed(it);
    ml->run(FORWARD);
    mr->run(BACKWARD);
    mlSpeed = ot;
    mrSpeed = it;
  }
}

void turnLeft() {
  if (mlSpeed != it || mrSpeed != ot) {
    ml->setSpeed(it);
    mr->setSpeed(ot);
    ml->run(BACKWARD);
    mr->run(FORWARD);
    mlSpeed = it;
    mrSpeed = ot;
  }
}

void followLine() {
  leftLSReading = digitalRead(leftLSPin);
  rightLSReading = digitalRead(rightLSPin);
  farRightLSReading = digitalRead(farRightLSPin);
  if (leftLSReading == WHITE && rightLSReading == BLACK) turnLeft();
  else if (leftLSReading == BLACK && rightLSReading == WHITE && farRightLSReading == BLACK) turnRight();
  else if (leftUS < 10) tunnelDriving();
  else setNormalSpeed();
}

void tunnelDriving() {
  if (leftUS > tunnelLeftClearance + 0.5) turnLeft();
  else if (leftUS < tunnelLeftClearance - 0.5) turnRight();
  else setNormalSpeed();
}

void hardLeft() {
  ml->setSpeed(255);
  mr->setSpeed(255);
  delay(1500);
  ml->setSpeed(10);
  mr->setSpeed(255);
  while (digitalRead(rightLSPin) == BLACK) continue;
  delay(250);
  if (magnet) delay(500);
  ml->setSpeed(255);
  ml->run(BACKWARD);
  mr->run(BACKWARD);
  mr->setSpeed(0);
  delay(700);
  mr->setSpeed(255);
  delay(500);
  ml->setSpeed(0);
  while (digitalRead(leftLSPin) == BLACK) continue;
  ml->setSpeed(255);
  ml->run(FORWARD);
  mr->run(FORWARD); 
  mlSpeed = normalSpeed;
  mrSpeed = normalSpeed;
  turn = true;
  timeHard = millis();
}

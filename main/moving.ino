void lowerSpeed() {
  ml->setSpeed(slowBlock);
  mr->setSpeed(slowBlock);
}

void normalSpeed() {
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
}


// first move forward x m, turn right
void initial() {
  //hard code going forward
}

// if right is white turn right, if left is white turn left
void followLine() {
  if (leftLine == WHITE && rightLine == BLACK) mr->setSpeed(innerTurnSpeed);
  else if (leftLine == BLACK && rightLine == WHITE) ml->setSpeed(innerTurnSpeed);
  else normalSpeed();
}

// if IR sensor detect enter tunnel
void tunnelDriving() {
  if (leftUS < tunnelLeftClearance + 0.5) mr->setSpeed(innerTurnSpeed);
  else if (leftUS > tunnelLeftClearance - 0.5) ml->setSpeed(innerTurnSpeed);
  else normalSpeed();
}
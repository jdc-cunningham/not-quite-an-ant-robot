/**
 * this function is intended to move servos together at the same time
 * it takes the largest rotation range and loops through positions
 * it is slightly assymetrical depending on how varied the ranges are since
 * it starts on the left side eg. 0 to whatever range eg.
 * 0, 10, 40, 50 can see how one set will finish before the next.
 * should be proportional
 */

void moveServos(int arrServosRange, int servoCount, int motionDelay) { // servo count passed in since no arr.length
  if (servoCount > 0) {
    // get max range
    int maxRange = 0;
    for (int curServo = 0; curServo < servoCount; curServo += 1) {
//      if (arrServosRange[
    }
  }
//  int pos1[2] = {50, 80};
//  int pos2[2] = {105, 65};
//  int pos3[2] = {125, 100};
//  int pos4[2] = {85, 130};
//
//  int pos = 0;
//  for (pos = 0; pos < 45; pos += 1) { // largest difference
//    Serial.println(pos);
//    // lazy way
//    if (pos1[0] + pos < pos1[1]) {
//      frontRightInnerServo.write(pos1[0] + pos);
//    }
//    if (pos2[0] - pos > pos2[1]) {
//      backLeftInnerServo.write(pos2[0] - pos);
//    }
//    if (pos3[0] - pos > pos3[1]) {
//      frontLeftInnerServo.write(pos3[0] - pos);
//    }
//    if (pos4[0] + pos < pos4[1]) {
//      backRightInnerServo.write(pos3[0] + pos);
//    }
//    delay(servoMotionDelay);
//  }
}

void moveForwardHalfLeft() {
  int pos3[2] = {125, 100};
  int pos4[2] = {130, 85};

  int pos = 0;
  for (pos = 0; pos < 45; pos += 1) { // largest difference
    Serial.println(pos);
    // lazy way
    if (pos3[0] - pos > pos3[1]) {
      frontLeftInnerServo.write(pos3[0] - pos);
    }
    if (pos4[0] - pos > pos4[1]) {
      backRightInnerServo.write(pos4[0] - pos);
    }
    delay(servoMotionDelay);
  }
}

void liftLeftLegs() {
  servoMotion(frontLeftOuterServo, 80, 105, servoMotionDelay);
  servoMotion(backRightOuterServo, 100, 70, servoMotionDelay);
}

void lowerRightLegs() {
  servoMotion(frontRightOuterServo, 60, 100, servoMotionDelay);
  servoMotion(backLeftOuterServo, 90, 60, servoMotionDelay);
}

void liftMiddleLegs() {
  servoMotion(middleServo, 50, 30, servoMotionDelay);
}

void lowerMiddleLegs() {
  servoMotion(middleServo, 30, 50, servoMotionDelay);
}

//frontRightInnerServo.write(90);
//frontRightOuterServo.write(110);
//frontLeftInnerServo.write(90);
//frontLeftOuterServo.write(60);
//backRightInnerServo.write(130);
//backRightOuterServo.write(110);
//backLeftInnerServo.write(65);
//backLeftOuterServo.write(40);
//middleServo.write(50);

void moveForward() {
  // front right
  servoMotion(frontRightOuterServo, 110, 60, servoMotionDelay); // raise leg
  servoMotion(frontRightInnerServo, 80, 50, servoMotionDelay); // swing forward
  servoMotion(frontRightOuterServo, 60, 110, servoMotionDelay); // lower leg

  // back left
  servoMotion(backLeftOuterServo, 40, 90, servoMotionDelay); // lift up
  servoMotion(backLeftInnerServo, 65, 105, servoMotionDelay); // swing forward
  servoMotion(backLeftOuterServo, 90, 40, servoMotionDelay); // lower

  // front left
  servoMotion(frontLeftOuterServo, 60, 105, servoMotionDelay); // raise leg
  servoMotion(frontLeftInnerServo, 100, 125, servoMotionDelay); // swing forward
  servoMotion(frontLeftOuterServo, 105, 60, servoMotionDelay); // lower leg

  // back right
  servoMotion(backRightOuterServo, 110, 70, servoMotionDelay); // lift up
  servoMotion(backRightInnerServo, 130, 85, servoMotionDelay); // swing forward
  servoMotion(backRightOuterServo, 70, 110, servoMotionDelay); // lower

  // lol all together move forward
//  servoMotionMulti({
//    {frontRightInnerServo, 60, 80, servoMotionDelay}, // 20
//    {backLeftInnerServo, 95, 75, servoMotionDelay}, // 20
//    {frontLeftInnerServo, 115, 100, servoMotionDelay}, // 15
//    {backRightInnerServo, 95, 120, servoMotionDelay} // 25
//  });

  liftMiddleLegs();

  int pos1[2] = {50, 80};
  int pos2[2] = {105, 65};
  int pos3[2] = {125, 100};
  int pos4[2] = {85, 130};

  int pos = 0;
  for (pos = 0; pos < 45; pos += 1) { // largest difference
    Serial.println(pos);
    // lazy way
    if (pos1[0] + pos < pos1[1]) {
      frontRightInnerServo.write(pos1[0] + pos);
    }
    if (pos2[0] - pos > pos2[1]) {
      backLeftInnerServo.write(pos2[0] - pos);
    }
    if (pos3[0] - pos > pos3[1]) {
      frontLeftInnerServo.write(pos3[0] - pos);
    }
    if (pos4[0] + pos < pos4[1]) {
      backRightInnerServo.write(pos4[0] + pos);
    }
    delay(servoMotionDelay);
  }

  lowerMiddleLegs();
}

void moveAllLegsForward() {
  liftMiddleLegs();

  int pos1[2] = {50, 80};
  int pos2[2] = {105, 65};
  int pos3[2] = {125, 100};
  int pos4[2] = {85, 130};

  int pos = 0;
  for (pos = 0; pos < 45; pos += 1) { // largest difference
    Serial.println(pos);
    // lazy way
    if (pos1[0] + pos < pos1[1]) {
      frontRightInnerServo.write(pos1[0] + pos);
    }
    if (pos2[0] - pos > pos2[1]) {
      backLeftInnerServo.write(pos2[0] - pos);
    }
    if (pos3[0] - pos > pos3[1]) {
      frontLeftInnerServo.write(pos3[0] - pos);
    }
    if (pos4[0] + pos < pos4[1]) {
      backRightInnerServo.write(pos4[0] + pos);
    }
    delay(servoMotionDelay);
  }

  lowerMiddleLegs();
}

void moveForwardAlt() {
  // front right
//  servoMotion(frontRightOuterServo, 110, 60, servoMotionDelay); // raise leg
//  servoMotion(backLeftOuterServo, 40, 90, servoMotionDelay); // lift up

  int pos = 0;
  int posa[2] = {110, 60};
  int posb[2] = {40, 90};

  for (pos = 0; pos < 50; pos += 1) { // largest difference
    // lazy way
    if (posa[0] - pos > posa[1]) {
      frontRightOuterServo.write(posa[0] - pos);
    }
    if (posb[0] + pos < posb[1]) {
      backLeftOuterServo.write(posb[0] + pos);
    }
    delay(servoMotionDelay);
  }
  
//  servoMotion(frontRightInnerServo, 80, 50, servoMotionDelay); // swing forward
//  servoMotion(backLeftInnerServo, 65, 105, servoMotionDelay); // swing forward

  int posc[2] = {80, 50};
  int posd[2] = {65, 105};

  for (pos = 0; pos < 40; pos += 1) { // largest difference
    // lazy way
    if (posc[0] - pos > posc[1]) {
      frontRightInnerServo.write(posc[0] - pos);
    }
    if (posd[0] + pos < posd[1]) {
      backLeftInnerServo.write(posd[0] + pos);
    }
    delay(servoMotionDelay);
  }
  
//  servoMotion(frontRightOuterServo, 60, 110, servoMotionDelay); // lower leg
//  servoMotion(backLeftOuterServo, 90, 40, servoMotionDelay); // lower

  int pose[2] = {60, 110};
  int posf[2] = {90, 40};


  for (pos = 0; pos < 50; pos += 1) { // largest difference
    // lazy way
    if (pose[0] + pos < pose[1]) {
      frontRightOuterServo.write(pose[0] + pos);
    }
    if (posf[0] - pos > posf[1]) {
      backLeftOuterServo.write(posf[0] - pos);
    }
    delay(servoMotionDelay);
  }

  // other set
//  servoMotion(frontLeftOuterServo, 60, 105, servoMotionDelay); // raise leg
//  servoMotion(backRightOuterServo, 110, 70, servoMotionDelay); // lift up

  int posg[2] = {60, 105};
  int posh[2] = {110, 70};


  for (pos = 0; pos < 45; pos += 1) { // largest difference
    // lazy way
    if (posg[0] + pos < posg[1]) {
      frontLeftOuterServo.write(posg[0] + pos);
    }
    if (posh[0] - pos > posh[1]) {
      backRightOuterServo.write(posh[0] - pos);
    }
    delay(servoMotionDelay);
  }

//  servoMotion(frontLeftInnerServo, 100, 125, servoMotionDelay); // swing forward
//  servoMotion(backRightInnerServo, 130, 85, servoMotionDelay); // swing forward

  int posi[2] = {100, 125};
  int posj[2] = {130, 85};

  for (pos = 0; pos < 45; pos += 1) { // largest difference
    // lazy way
    if (posi[0] + pos < posi[1]) {
      frontLeftInnerServo.write(posi[0] + pos);
    }
    if (posj[0] - pos > posj[1]) {
      backRightInnerServo.write(posj[0] - pos);
    }
    delay(servoMotionDelay);
  }
  
//  servoMotion(frontLeftOuterServo, 105, 60, servoMotionDelay); // lower leg
//  servoMotion(backRightOuterServo, 70, 110, servoMotionDelay); // lower

  int posk[2] = {105, 60};
  int posl[2] = {70, 110};


  for (pos = 0; pos < 45; pos += 1) { // largest difference
    // lazy way
    if (posk[0] - pos > posk[1]) {
      frontLeftOuterServo.write(posk[0] - pos);
    }
    if (posl[0] + pos < posl[1]) {
      backRightOuterServo.write(posl[0] + pos);
    }
    delay(servoMotionDelay);
  }

  moveAllLegsForward();
}

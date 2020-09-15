void setAndCenterServos() {
  // set servo pins
  frontRightInnerServo.attach(8); // 1 pos, assigning down from code
  frontRightOuterServo.attach(9); // 2
  frontLeftInnerServo.attach(6); // 3
  frontLeftOuterServo.attach(7); // 4
  backRightInnerServo.attach(10); // 5
  backRightOuterServo.attach(5); // 6
  backLeftInnerServo.attach(4); // 7
  backLeftOuterServo.attach(11); // 8
  middleServo.attach(12); // 9

  // set initial positions
  // TODO auto zero/level based on IMU
  frontRightInnerServo.write(90);
  frontRightOuterServo.write(110);
  frontLeftInnerServo.write(90);
  frontLeftOuterServo.write(60);
  backRightInnerServo.write(115);
  backRightOuterServo.write(40);
  backLeftInnerServo.write(80);
  backLeftOuterServo.write(110);
  middleServo.write(45);
}

void servoMotion(Servo servo, int initPos, int endingPos, int motionDelay) {
  int pos = 0;
  bool decrease = initPos > endingPos;

  if (decrease) {
    for (pos = initPos; pos > endingPos; pos -= 1) {
      servo.write(pos);
      delay(motionDelay);
    }
  } else {
    for (pos = initPos; pos < endingPos; pos += 1) {
      servo.write(pos);
      delay(motionDelay);
    }
  }
}

void liftMiddleLegs() {
  servoMotion(middleServo, 50, 25, servoMotionDelay);
}

void lowerMiddleLegs() {
  servoMotion(middleServo, 25, 50, servoMotionDelay);
}

void moveAllLegsForward() {
  liftMiddleLegs();

  int servoGroupArr[][3] = {
    {1, 50, 80},
    {7, 105, 80},
    {3, 125, 100},
    {5, 85, 115}
  };
 
  moveServos(
    servoGroupArr,
    4,
    servoMotionDelay
  );

  lowerMiddleLegs();
}

void moveAllLegsBackward() {
  liftMiddleLegs();

  int servoGroupArr[][3] = {
    {1, 90, 60},
    {7, 80, 105},
    {3, 90, 115},
    {5, 115, 85}
  };
 
  moveServos(
    servoGroupArr,
    4,
    servoMotionDelay
  );

  lowerMiddleLegs();
}

Servo getServoFromEnum(int servoEnum) {
  if (servoEnum == 1) {
    return frontRightInnerServo;
  } else if (servoEnum == 2) {
    return frontRightOuterServo;
  } else if (servoEnum == 3) {
    return frontLeftInnerServo;
  } else if (servoEnum == 4) {
    return frontLeftOuterServo;
  } else if (servoEnum == 5) {
    return backRightInnerServo;
  } else if (servoEnum == 6) {
    return backRightOuterServo;
  } else if (servoEnum == 7) {
    return backLeftInnerServo;
  } else if (servoEnum == 8) {
    return backLeftOuterServo;
  } else {
    return middleServo;
  }
}

/**
 * This function moves servos together at the same speed
 * there is a "bias" where the shortest motion will end first
 * @param {int} - array of arrays with the following: servo enum, start pos, end pos
 * @param {int} - array length
 * @param {int} - duration of motion
 */
void moveServos(int servoGroupArr[][3], int servoGroupArrLen, int motionDuration) {
  /**
   * loop through servos, find largest range between start/end pos
   * there is no error checking, I find coding in Arduino to be cumbersome */
  clearEspSerial(); // buffer
  motionInProgress = true;
  int largestServoRange = 0;

  for (int servoGroupIndex = 0; servoGroupIndex < servoGroupArrLen; servoGroupIndex++) {
    int range = 0;
    if (servoGroupArr[servoGroupIndex][1] < servoGroupArr[servoGroupIndex][2]) {
      // increase
      range = servoGroupArr[servoGroupIndex][2] - servoGroupArr[servoGroupIndex][1];
      if (range > largestServoRange) {
        largestServoRange = range;
      }
    } else {
      // decrease
      range = servoGroupArr[servoGroupIndex][1] - servoGroupArr[servoGroupIndex][2];
      if (range > largestServoRange) {
        largestServoRange = range;
      }
    }
  }

  /* do the motion on the servos going by largest range
   * this will update all the servo positions at the same rate
   * but some will finish earlier than others if the motion range is not the same */
  for (int pos = 0; pos < largestServoRange; pos++) {
    for(int servoGroupIndex = 0; servoGroupIndex < servoGroupArrLen; servoGroupIndex++) {
      if (servoGroupArr[servoGroupIndex][1] < servoGroupArr[servoGroupIndex][2]) {
        // increase
        if (servoGroupArr[servoGroupIndex][1] + pos < servoGroupArr[servoGroupIndex][2]) {
          getServoFromEnum(servoGroupArr[servoGroupIndex][0]).write(servoGroupArr[servoGroupIndex][1] + pos);
        }
      } else {
        // decrease
        if (servoGroupArr[servoGroupIndex][1] - pos > servoGroupArr[servoGroupIndex][2]) {
          getServoFromEnum(servoGroupArr[servoGroupIndex][0]).write(servoGroupArr[servoGroupIndex][1] - pos);
        }
      }
    }
    delay(motionDuration);
  }

  motionInProgress = false;
}

void moveForward() {
  // front right, back left - outer servos (pitch)
  int servoGroupArr1[][3] = {
    {2, 110, 60},
    {8, 110, 60}
  };

  moveServos(
    servoGroupArr1,
    2,
    servoMotionDelay
  );

  // front right, back left - inner servos (swivel)
  int servoGroupArr2[][3] = {
    {1, 90, 60},
    {7, 80, 105}
  };

  moveServos(
    servoGroupArr2,
    2,
    servoMotionDelay
  );

  // front right, back left - outer servos (pitch)
  int servoGroupArr3[][3] = {
    {2, 60, 110},
    {8, 60, 110}
  };
  
  moveServos(
    servoGroupArr3,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr4[][3] = {
    {4, 60, 105},
    {6, 40, 80}
  };

  moveServos(
    servoGroupArr4,
    2,
    servoMotionDelay
  );
  
  // front left, back right - inner servos (swivel)
  int servoGroupArr5[][3] = {
    {3, 90, 115},
    {5, 115, 85}
  };

  moveServos(
    servoGroupArr5,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr6[][3] = {
    {4, 105, 60},
    {6, 80, 40}
  };

  moveServos(
    servoGroupArr6,
    2,
    servoMotionDelay
  );

  moveAllLegsForward();
}

void moveBackward() {
  // front right, back left - outer servos (pitch)
  int servoGroupArr1[][3] = {
    {2, 110, 60},
    {8, 110, 60}
  };

  moveServos(
    servoGroupArr1,
    2,
    servoMotionDelay
  );

  // front right, back left - inner servos (swivel)
  int servoGroupArr2[][3] = {
    {1, 60, 90},
    {7, 105, 80}
  };

  moveServos(
    servoGroupArr2,
    2,
    servoMotionDelay
  );

  // front right, back left - outer servos (pitch)
  int servoGroupArr3[][3] = {
    {2, 60, 110},
    {8, 60, 110}
  };
  
  moveServos(
    servoGroupArr3,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr4[][3] = {
    {4, 60, 105},
    {6, 40, 80}
  };

  moveServos(
    servoGroupArr4,
    2,
    servoMotionDelay
  );
  
  // front left, back right - inner servos (swivel)
  int servoGroupArr5[][3] = {
    {3, 115, 90},
    {5, 85, 135}
  };

  moveServos(
    servoGroupArr5,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr6[][3] = {
    {4, 105, 60},
    {6, 80, 40}
  };

  moveServos(
    servoGroupArr6,
    2,
    servoMotionDelay
  );

  moveAllLegsBackward();
}

void rotateAllLegsRight() {
  liftMiddleLegs();

  // front right, back left - inner servos (swivel)
  int servoGroupArr[][3] = {
    {1, 60, 90},
    {7, 25, 80},
    {3, 65, 90},
    {5, 85, 115}
  };

  moveServos(
    servoGroupArr,
    4,
    servoMotionDelay
  );

  lowerMiddleLegs();
}

void rotateLeft() {
  // ront right, back left - outer servos (pitch)
  int servoGroupArr1[][3] = {
    {2, 110, 60},
    {8, 110, 60}
  };

  moveServos(
    servoGroupArr1,
    2,
    servoMotionDelay
  );

  // front right, back left - inner servos (swivel)
  int servoGroupArr2[][3] = {
    {1, 90, 60},
    {7, 80, 25}
  };

  moveServos(
    servoGroupArr2,
    2,
    servoMotionDelay
  );

  // front right, back left - outer servos (pitch)
  int servoGroupArr3[][3] = {
    {2, 60, 110},
    {8, 60, 110}
  };
  
  moveServos(
    servoGroupArr3,
    2,
    servoMotionDelay
  );


  // front left, back right - outer servos (pitch)
  int servoGroupArr4[][3] = {
    {4, 60, 105},
    {6, 40, 80}
  };

  moveServos(
    servoGroupArr4,
    2,
    servoMotionDelay
  );
  
  // front left, back right - inner servos (swivel)
  int servoGroupArr5[][3] = {
    {3, 90, 65},
    {5, 115, 85}
  };

  moveServos(
    servoGroupArr5,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr6[][3] = {
    {4, 105, 60},
    {6, 80, 40}
  };

  moveServos(
    servoGroupArr6,
    2,
    servoMotionDelay
  );

  rotateAllLegsRight(); // goes left
}

void rotateAllLegsLeft() {
  liftMiddleLegs();

  // front right, back left - inner servos (swivel)
  int servoGroupArr[][3] = {
    {1, 120, 90},
    {7, 105, 80},
    {3, 115, 90},
    {5, 175, 115}
  };

  moveServos(
    servoGroupArr,
    4,
    servoMotionDelay
  );

  lowerMiddleLegs();
}

void rotateRight() {
  // front right, back left - outer servos (pitch)
  int servoGroupArr1[][3] = {
    {2, 110, 60},
    {8, 110, 60}
  };

  moveServos(
    servoGroupArr1,
    2,
    servoMotionDelay
  );

  // front right, back left - inner servos (swivel)
  int servoGroupArr2[][3] = {
    {1, 90, 120},
    {7, 80, 105}
  };

  moveServos(
    servoGroupArr2,
    2,
    servoMotionDelay
  );

  // front right, back left - outer servos (pitch)
  int servoGroupArr3[][3] = {
    {2, 60, 110},
    {8, 60, 110}
  };
  
  moveServos(
    servoGroupArr3,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr4[][3] = {
    {4, 60, 105},
    {6, 40, 80}
  };

  moveServos(
    servoGroupArr4,
    2,
    servoMotionDelay
  );
  
  // front left, back right - inner servos (swivel)
  int servoGroupArr5[][3] = {
    {3, 90, 115},
    {5, 115, 175}
  };

  moveServos(
    servoGroupArr5,
    2,
    servoMotionDelay
  );

  // front left, back right - outer servos (pitch)
  int servoGroupArr6[][3] = {
    {4, 105, 60},
    {6, 80, 40}
  };

  moveServos(
    servoGroupArr6,
    2,
    servoMotionDelay
  );

  rotateAllLegsLeft(); // goes left
}

void swayLeft() {
  int servoGroupArr[][3] = {
    {4, 60, 40}, // frontLeftOuterServo
    {2, 110, 90}, // frontRightOuterServo
    {8, 40, 20}, // backLeftOuterServo
    {6, 110, 90} // backRightOuterServo
  };

  moveServos(
    servoGroupArr,
    4,
    servoMotionDelay
  );
}

// FEATUERE: lower height by pitching legs out, need to update resting positions

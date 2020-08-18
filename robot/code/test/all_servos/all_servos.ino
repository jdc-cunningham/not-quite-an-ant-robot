/**
 * all servos plugged in
 * visual:
 * 
 *     FLO          FRO
 *         FLI  FRI
 *         
 *         BLI  BRI
 *     BLO          BRO
 *
 */

#include <Servo.h>
Servo frontRightInnerServo;
Servo frontRightOuterServo;
Servo frontLeftInnerServo;
Servo frontLeftOuterServo;
Servo backRightInnerServo;
Servo backRightOuterServo;
Servo backLeftInnerServo;
Servo backLeftOuterServo;
Servo middleServo;

int servoMotionDelay = 10; // how fast the servo moves a deg in ms

void setAndCenterServos() {
  // set servo pins
  frontRightInnerServo.attach(8);
  frontRightOuterServo.attach(9);
  frontLeftInnerServo.attach(6);
  frontLeftOuterServo.attach(7);
  backRightInnerServo.attach(10);
  backRightOuterServo.attach(11);
  backLeftInnerServo.attach(4);
  backLeftOuterServo.attach(5);
  middleServo.attach(12);

  // set initial positions
  // TODO auto zero/level based on IMU
  frontRightInnerServo.write(90);
  frontRightOuterServo.write(110);
  frontLeftInnerServo.write(90);
  frontLeftOuterServo.write(60);
  backRightInnerServo.write(130);
  backRightOuterServo.write(110);
  backLeftInnerServo.write(65);
  backLeftOuterServo.write(40);
  middleServo.write(55);
}

// slow motion
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

//void servoMotionMulti(int commArr[][]) {
//  
//}

void liftRightLegs() {
  // front right
  servoMotion(frontRightOuterServo, 110, 60, servoMotionDelay); // raise leg
//  servoMotion(frontRightInnerServo, 80, 50, servoMotionDelay); // swing forward
//  servoMotion(frontRightOuterServo, 60, 100, servoMotionDelay); // lower leg

  // back left
  servoMotion(backLeftOuterServo, 40, 90, servoMotionDelay); // lift up
//  servoMotion(backLeftInnerServo, 65, 105, servoMotionDelay); // swing forward
//  servoMotion(backLeftOuterServo, 90, 60, servoMotionDelay); // lower
}

void moveForwardHalfRight() {
  int pos1[2] = {90, 60};
  int pos2[2] = {65, 95};

  int pos = 0;
  for (pos = 0; pos < 30; pos += 1) { // largest difference
    Serial.println(pos);
    // lazy way
    if (pos1[0] - pos > pos1[1]) {
      frontRightInnerServo.write(pos1[0] - pos);
    }
    if (pos2[0] + pos < pos2[1]) {
      backLeftInnerServo.write(pos2[0] + pos);
    }
    delay(servoMotionDelay);
  }
}

void moveAllForward() {
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
//      backRightInnerServo.write(pos4[0] + pos);
//    }
//    delay(servoMotionDelay);
//  }
}

void setup() {
  Serial.begin(115200);
  setAndCenterServos();
  delay(500);
//   moveForward();
//  liftRightLegs();
//  moveForwardHalfRight();
//  lowerRightLegs();
//  liftLeftLegs();
//  moveForwardHalfLeft();
//  liftMiddleLegs();
//  moveAllForward();
//  lowerMiddleLegs();
}

void loop() {
  // put your main code here, to run repeatedly:
  moveForwardAlt();
  delay(2000);
}

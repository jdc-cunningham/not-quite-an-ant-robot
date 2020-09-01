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

#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial ESPserial(2, 3); // rx tx
Servo frontRightInnerServo;
Servo frontRightOuterServo;
Servo frontLeftInnerServo;
Servo frontLeftOuterServo;
Servo backRightInnerServo;
Servo backRightOuterServo;
Servo backLeftInnerServo;
Servo backLeftOuterServo;
Servo middleServo;

int servoMotionDelay = 6; // how fast the servo moves a deg in ms
int usSensorTrigPin = 13;
int usSensorEchoPin = A0;
int usSensorTravelDuration;
int usSensorMeasuredDistance;
int avoidRotateCounter = 0;
bool avoidRotateDirectionLeft = true;

void setup() {
  setAndCenterServos();
  Serial.begin(115200);
  ESPserial.begin(115200);

  // setup ultrasonic sensor
  pinMode(usSensorTrigPin, OUTPUT);
  pinMode(usSensorEchoPin, INPUT);
}

String commandStr;
int appendCounter = 0;
bool commandMatch = false;
bool motionInProgress = false;
String commIntRange = "23456789";

void loop() {
  /**
  * current commands:
  * F - forward
  * L - rotate left
  * R - rotate right
  * B - backwards
  * # - set speed of servo eg. ms delay per degree rotation
  * Software Serial is not reliable at 115200, even checking 2 characters has too many errors
  */
  while (ESPserial.available()) {
    char c = ESPserial.read();
    commandStr += c;
    appendCounter += 1;

    Serial.println(commandStr);

    if (appendCounter > 1) {
      commandStr = "";
      appendCounter = 0;
    } else {
      usSensorPing();
      if (obstacleDetected()) {
        rotateLeft();
        return;
      }

      if (commandStr.indexOf("F") > -1 && !motionInProgress) {
        commandMatch = true;
        moveForward();
      } else if (commandStr.indexOf("L") > -1 && !motionInProgress) {
        commandMatch = true;
        rotateLeft();
      } else if (commandStr.indexOf("R") > -1 && !motionInProgress) {
        commandMatch = true;
        rotateRight();
      } else if (commandStr.indexOf("B") > -1 && !motionInProgress) {
        commandMatch = true;
        moveBackward();
      } else if (commIntRange.indexOf(commandStr) > -1) {
         // 2 is really fast relatively, and anything above 10 is really slow
        if (commandStr.toInt() >= 2 && commandStr.toInt() < 10) { // should go up to 10 but 1 char is easier to check
          servoMotionDelay = commandStr.toInt();
        }
      }

      if (commandMatch) {
        commandStr = "";
        appendCounter = 0;
        commandMatch = false;
      }
    }
  }

  // moveForward();
  // moveAllLegsBackward();
  // moveBackward();
  // setAndCenterServos();
  // rotateLeft();
  // rotateRight();
  // swayLeft();

  // delay(60000);
}

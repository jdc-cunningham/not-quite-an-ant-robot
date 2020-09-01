void usSensorPing() {
    // referencing old project
    // https://github.com/jdc-cunningham/noob-robotics/blob/master/taildragger-ultrasound-mapping/code/motion_1_ultrasonic_od_all_sensors_1__basic-od-logic/motion_1_ultrasonic_od_all_sensors_1__basic-od-logic.ino#L110
    digitalWrite(usSensorTrigPin, LOW); // clear pin
    delayMicroseconds(2);
    digitalWrite(usSensorTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(usSensorTrigPin, LOW);
    usSensorTravelDuration = pulseIn(usSensorEchoPin, HIGH);
    usSensorMeasuredDistance = usSensorTravelDuration * 0.0133 / 2; // distance in inches
    Serial.println(usSensorMeasuredDistance);
}

// regular motion using ultrasonic sensor
// aproximately 5 turns for 90 deg
bool obstacleDetected() {
    return usSensorMeasuredDistance <= 7;
}
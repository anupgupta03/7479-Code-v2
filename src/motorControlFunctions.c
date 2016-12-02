/**
 * @Date:   2016-10-22T14:32:57+11:00
 * @Last modified time: 2016-11-23T11:35:39+11:00
 */

#include "../include/main.h"
#include "../include/motorControlFunctions.h"

float eDist(pos posFrom, pos posTo){
	  return sqrt(square(posTo.x - posFrom.x) + square(posTo.y - posFrom.y));
}

float dHeading(pos posFrom, pos posTo){
	  return radToDeg(atan2((posTo.y - posFrom.y), (posTo.x - posFrom.x)));
}

int fixAngle(int angle){
	  return (angle + 180)%360 - 180;
}

void waitForZero(int *value) {
	  while (*value != 0) delay(20);
}

float cJoyThreshold(int input) {
	  return (abs(input) > JOYSTICK_THRESHOLD) ? (float)(mapCubic(input)) : 0.0;
}

void toggleDigitalPort(unsigned port) {
	  digitalWrite(port, (digitalRead(port) == 1 ? 0 : 1));
}

void setLiftLeft(const int power) {
	  switch (LIFT_SLEW_CONTROL_ENABLED) {
	  case true:
		    setMotorSpeed(MOTOR_LIFT_LEFT_TOP, (-1 * power));
		    setMotorSpeed(MOTOR_LIFT_LEFT_MID, (-1 * power));
		    setMotorSpeed(MOTOR_LIFT_LEFT_BOT, (-1 * power));
		    break;
	  case false:
		    motorSet(MOTOR_LIFT_LEFT_TOP, (-1 * power));
		    motorSet(MOTOR_LIFT_LEFT_MID, (-1 * power));
		    motorSet(MOTOR_LIFT_LEFT_BOT, (-1 * power));
		    break;
	  }
}

void setLiftRight(const int power) {
	  switch (LIFT_SLEW_CONTROL_ENABLED) {
	  case true:
		    setMotorSpeed(MOTOR_LIFT_RIGHT_TOP, power);
		    setMotorSpeed(MOTOR_LIFT_RIGHT_MID, -1 * power);
		    setMotorSpeed(MOTOR_LIFT_RIGHT_BOT, power);
		    break;
	  case false:
		    motorSet(MOTOR_LIFT_RIGHT_TOP, power);
		    motorSet(MOTOR_LIFT_RIGHT_MID, -1 * power);
		    motorSet(MOTOR_LIFT_RIGHT_BOT, power);
		    break;
	  }
}

void setDriveLeft(const int power) {
	  switch (BASE_SLEW_CONTROL_ENABLED) {
	  case true:
		    setMotorSpeed(MOTOR_BASE_FRONT_LEFT, power);
		    setMotorSpeed(MOTOR_BASE_BACK_LEFT, power);
		    break;
	  case false:
		    motorSet(MOTOR_BASE_FRONT_LEFT, power);
		    motorSet(MOTOR_BASE_BACK_LEFT, power);
		    break;
	  }
}

void setDriveRight(const int power) {
	  switch (BASE_SLEW_CONTROL_ENABLED) {
	  case true:
		    setMotorSpeed(MOTOR_BASE_FRONT_RIGHT, -1 * power);
		    setMotorSpeed(MOTOR_BASE_BACK_RIGHT, -1 * power);
		    break;
	  case false:
		    motorSet(MOTOR_BASE_FRONT_RIGHT, -1 * power);
		    motorSet(MOTOR_BASE_BACK_RIGHT, -1 * power);
		    break;
	  }

}

void setLift(const int power) {
	  setLiftLeft(-1 * power);
	  setLiftRight(-1 * (power + (sign(abs(encoderGet(enc_liftLeft)) - abs(encoderGet(enc_liftRight))) * power * 0.1)));

}

void driveTime(const int l_power, const int r_power, const int timeMs) {
	  unsigned startingTime = millis();
	  while (startingTime + timeMs > millis()) {
		    setDriveLeft(l_power);
		    setDriveRight(r_power);
	  }
	  setDriveLeft(0);
	  setDriveRight(0);
}

void driveStraightTime(const int power, const unsigned timeMs) {
	  int initialLeft = encoderGet(enc_baseLeft);
	  int initialRight = encoderGet(enc_baseRight);
	  unsigned startingTime = millis();
	  // Drive at full power for 80% of ticks
	  while (startingTime + (timeMs * 0.8) > millis()) {
		    setDriveLeft(power);
		    setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
		    delay(20);
	  }
	  // Drive at 1/3 Power for remaining 20% of ticks
	  while (startingTime > millis()) {
		    setDriveLeft((power / 3));
		    setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
		    delay(20);
	  }
	  // Stop
	  driveTime(-1 * (power / 2), -1 * (power / 2), 100);
	  setDriveLeft(0);
	  setDriveRight(0);
}

void turnTime(const int power, const int timeMs) {
	  unsigned int startingTime = millis();
	  while (startingTime + timeMs > millis()) {
		    setDriveLeft(-1 * power);
		    setDriveRight(power);
	  }
	  setDriveLeft(0.5 * power);
	  setDriveRight(-0.5 * power);
	  delay(75);
	  setDriveRight(0);
	  setDriveLeft(0);

}

void driveQuad(const int power, const int ticks) {

	  int initialLeft = encoderGet(enc_baseLeft);
	  int initialRight = encoderGet(enc_baseRight);
	  // Drive at full power for 80% of ticks
	  while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.8)) {
		    setDriveLeft(power);
		    setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
		    delay(20);
	  }
	  // Drive at 1/3 Power for remaining 20% of ticks
	  while (encoderGet(enc_baseLeft) < initialLeft) {
		    setDriveLeft((power / 3));
		    setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
		    delay(20);
	  }
	  // Stop
	  driveTime(-1 * (power / 2), -1 * (power / 2), 100);
	  setDriveLeft(0);
	  setDriveRight(0);

}

void turnQuad(const int power, const int ticks) {

	  int initialLeft = encoderGet(enc_baseLeft);
	  int initialRight = encoderGet(enc_baseRight);

	  while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.6)) {
		    setDriveLeft(-1 * power);
		    setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
		    delay(20);
	  }

	  while (encoderGet(enc_baseLeft) < initialLeft) {
		    setDriveLeft((-1 * power / 3));
		    setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
		    delay(20);
	  }
	  //Drive
	  turnTime(-1 * (power / 2), 100);
	  setDriveLeft(0);
	  setDriveRight(0);

}

void driveQuadPID(const int ticks){
	  pidController pid;
	  lcdClear(LCD_PORT);

	  // int initialLeft = encoderGet(enc_baseLeft);
	  // int initialRight = encoderGet(enc_baseRight);
	  init_PID(&pid, 0.001, 0.00001, 0.3, 0.15, 0.15);
	  float targetTicks = encoderGet(enc_baseLeft) + ticks;
	  step_PID(&pid, encoderGet(enc_baseLeft), targetTicks);
	  _Bool wasBad = abs(targetTicks - encoderGet(enc_baseLeft)) > 10;
	  while (abs(targetTicks - encoderGet(enc_baseLeft)) > 10 || wasBad)
	  {
		    wasBad = abs(targetTicks - encoderGet(enc_baseLeft)) > 10;
		    step_PID(&pid, encoderGet(enc_baseLeft), targetTicks);
		    setDriveLeft(pid.out * 127);
		    setDriveRight(pid.out * 127);
		    lcdPrint(LCD_PORT, 1, "%d, %d", encoderGet(enc_baseLeft), encoderGet(enc_baseRight));

		    delay(100);
		    //  + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * pid.out * 127 * 0.1))
	  }
	  setDriveLeft(0);
	  setDriveRight(0);
}

void turnGyro(const int power, const int deg) {
}

void moveToPosition(OdometricLocalizer *odo, float xPos, float yPos){
	  // pidController positionPid;
	  // pidController headingPid;
	  // pos targetPos;
	  //
	  // targetPos.x = xPos;
	  // targetPos.y = yPos;
	  //
	  // init_PID(&positionPid, 1, 0, 0, 2);
	  // init_PID(&headingPid, 1, 0, 0, 2);
	  //
	  // float currentDistance = eDist(odo->currentPosition, targetPos);
	  // float heading = fixAngle(dHeading(odo->currentPosition, targetPos));
	  //
	  // while (1==1) {
	  //
	  //     currentDistance = eDist(odo->currentPosition, targetPos);
	  //     heading = fixAngle(dHeading(odo->currentPosition, targetPos));
	  //
	  //     step_PID(&positionPid, currentDistance, 0);
	  //     step_PID(&headingPid, heading, 0);
	  //
	  //     setDriveLeft((positionPid.out * 127) - (headingPid.out * 127));
	  //     setDriveLeft((positionPid.out * 127) + (headingPid.out * 127));
	  //
	  //     delay(100);
	  // }
}

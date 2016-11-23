/**
 * @Date:   2016-10-22T14:32:57+11:00
* @Last modified time: 2016-11-23T11:35:59+11:00
 */
#include "../include/slewRateController.h"

/**
 * Main array of drive motor objects
 */
driveMotor driveMotors[MOTOR_NUM];
/*
 * Adds and initializes a motor (by name) to the motor array
 */
void addMotor(const int port, float slewRate) {
	  driveMotor* m = &(driveMotors[port]);

	  m->reqSpeed = 0;
	  m->artSpeed = 0;
	  m->slew = slewRate;
	  m->active = true;
}

void setMotorSpeed(const int index, const int power) {
	  driveMotors[index].reqSpeed = (power);
}

void setMotorSpeed_Bypass(const int index, const int power) {
	  driveMotors[index].reqSpeed = (power);
	  driveMotors[index].artSpeed = (power);
}
void setMotorSlew(const int index, const float rate) {
	  driveMotors[index].slew = (rate);
}
driveMotor getMotor(const int index) {
	  return driveMotors[index];
}
int getMotorSpeed(const int index) {
	  return driveMotors[index].reqSpeed;
}
void setMotorActive(const int index) {
	  driveMotors[index].active = true;
}
void setMotorInactive(const int index) {
	  driveMotors[index].active = false;
}

void slewrateControl_task(void *ignore) {
	  //Index of current motor
	  unsigned int motorIndex;
	  //Requested speed of current motor
	  int motorTmpReq;
	  //Artificial speed of current motor
	  float motorTmpArtSpd;
	  //Current motor
	  driveMotor *currentMotor;

	  while (true) {
		    //Batch motor power update
		    for (motorIndex = 0; motorIndex < MOTOR_NUM; motorIndex++) {
			      currentMotor = &(driveMotors[motorIndex]);
			      //Skip over a motor if it isn't active
			      if (!currentMotor->active) continue;

			      //Keep internal memory access to a minimum
			      motorTmpArtSpd = currentMotor->artSpeed;
			      motorTmpReq = currentMotor->reqSpeed;

			      //If the motor value needs to change
			      if (motorTmpArtSpd != motorTmpReq) {
					//Increase motor value
					if (motorTmpReq > motorTmpArtSpd) {
						  motorTmpArtSpd += currentMotor->slew;

						  //Limit speed
						  motorTmpArtSpd = motorTmpArtSpd > motorTmpReq ? motorTmpReq : motorTmpArtSpd;
					}

					//Decrease motor value
					if (motorTmpReq < motorTmpArtSpd) {
						  motorTmpArtSpd -= currentMotor->slew;

						  //Limit speed
						  motorTmpArtSpd = motorTmpArtSpd < motorTmpReq ? motorTmpReq : motorTmpArtSpd;
					}

					//Bound speed
					motorTmpArtSpd = motorTmpArtSpd > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE : motorTmpArtSpd;
					motorTmpArtSpd = motorTmpArtSpd < MOTOR_MIN_VALUE ? MOTOR_MIN_VALUE : motorTmpArtSpd;

					//Send updated speed to motor
					motorSet(motorIndex, (int) motorTmpArtSpd);

					//Send updated speed back to current motor
					currentMotor->artSpeed = motorTmpArtSpd;
			      }
		    }
		    delay(MOTOR_TASK_DELAY);
	  }
}

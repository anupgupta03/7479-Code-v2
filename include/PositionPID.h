/*
 * PositionPID.h
 *
 *  Created on: Oct 5, 2016
 *      Author: natty
 */

#ifndef SRC_POSITIONPID_H_
#define SRC_POSITIONPID_H_

//PID Controller representation
typedef struct pos_PID_t {
	//PID constants
	float kP;
	float kI;
	float kD;
	float kBias;

	//PID calculations
	int error;
	int prevError;
	int integral;
	int derivative;

	//PID limits
	int errorThreshold;
	int integralLimit;

	//Timestep
	float dt;
	int prevTime;

	//Input
	Encoder sensor;
	int targetPos;

	//Output
	int outVal;
} pos_PID;

//Initializes a position PID controller
void pos_PID_InitController(pos_PID *pid, const Encoder sensor, const float kP,
		const float kI, const float kD, const float kBias,
		const int errorThreshold, const int integralLimit);

//Sets the target position
void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos);

//Gets the current error
int pos_PID_GetError(pos_PID *pid);

//Gets the current output
int pos_PID_GetOutput(pos_PID *pid);

//Steps the controller's calculations
int pos_PID_StepController(pos_PID *pid);

#endif /* SRC_POSITIONPID_H_ */

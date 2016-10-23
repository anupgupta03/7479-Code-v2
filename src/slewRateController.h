/*
 * slewRateController.h
 *
 *  Created on: Oct 5, 2016
 *      Author: natty
 */

#ifndef SRC_SLEWRATECONTROLLER_H_
#define SRC_SLEWRATECONTROLLER_H_

#include "main.h"
//Motor general
#define MOTOR_NUM               10
#define MOTOR_MIN_VALUE         (-127) //Minimum power
#define MOTOR_MAX_VALUE         127    //Maximum power
#define MOTOR_DEFAULT_SLEW_RATE 10     //Feels like nearly no slewing to a driver
#define MOTOR_FAST_SLEW_RATE    256    //No slewing in output
#define MOTOR_SLOW_SLEW_RATE    350
#define LIFT_SLOW_SLEW_RATE     450
#define MOTOR_TASK_DELAY        5     //Wait 5ms between batch motor power updates

//Motor representation
typedef struct driveMotor_t {
    int reqSpeed;   //Input speed
    float artSpeed; //Artificial Speed
    float slew;     //Slew rate
    bool active;    //Whether or not to handle this motor
} driveMotor;

extern driveMotor driveMotors[MOTOR_NUM];

void addMotor(const int port, const float slewRate);

// Motor Control
void setMotorSpeed(const int index, const int power);
void setMotorSpeed_Bypass(const int index, const int power);
void setMotorSlew(const int index, const float rate);
driveMotor getMotor(const int index);
int getMotorSpeed(const int index);
void setMotorActive(const int index);
void setMotorInactive(const int index);

void slewrateControl_task(void *ignore);

#endif /* SRC_SLEWRATECONTROLLER_H_ */

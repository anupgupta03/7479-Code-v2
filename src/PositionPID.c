/*
 * Positionpid->c
 *
 *  Created on: Oct 5, 2016
 *      Author: natty
 */
#include "main.h"
#include "PositionPID.h"

void pos_PID_InitController(pos_PID *pid, const Encoder sensor, const float kP, const float kI, const float kD, const float kBias, const int errorThreshold, const int integralLimit)
{
  pid->kP = kP;
  pid->kI = kI;
  pid->kD = kD;
  pid->kBias = kBias;

  pid->error = 0;
  pid->prevError = 0;
  pid->integral = 0;
  pid->derivative = 0;

  pid->errorThreshold = errorThreshold;
  pid->integralLimit = integralLimit;

  pid->dt = 0;
  pid->prevTime = 0;

  pid->sensor = sensor;
  pid->targetPos = encoderGet(sensor);

  pid->outVal = 0;
}

void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos)
{
  pid->targetPos = targetPos;
}

int pos_PID_GetError(pos_PID *pid)
{
  return pid->error;
}

int pos_PID_GetOutput(pos_PID *pid)
{
  return pid->outVal;
}

int pos_PID_StepController(pos_PID *pid)
{
  //Calculate timestep
  pid->dt = (millis() - pid->prevTime) / 1000.0;
  pid->prevTime = millis();

  //Scrap dt if zero
  if (pid->dt == 0)
  {
    return 0;
  }

  //Calculate error
  pid->error = pid->targetPos - encoderGet(pid->sensor);

  //If error is large enough, calculate integral and limit to avoid windup
  if (abs(pid->error) > pid->errorThreshold && abs(pid->integral) < pid->integralLimit)
  {
    pid->integral = pid->integral + pid->error * pid->dt;

    //Reset integral if reached target or overshot
    if (pid->error == 0 || sign(pid->error) != sign(pid->prevError))
    {
      pid->integral = 0;
    }
    //Bound integral
    else
    {
      pid->integral = pid->integral * pid->kI > 127 ? 127.0 / pid->kI : pid->integral;
      pid->integral = pid->integral * pid->kI < -127 ? -127.0 / pid->kI : pid->integral;
    }
  }

  //Calculate derivative
  pid->derivative = (pid->error - pid->prevError) / pid->dt;
  pid->prevError = pid->error;

  //Calculate output
  pid->outVal = (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD) + pid->kBias;

  return pid->outVal;
}

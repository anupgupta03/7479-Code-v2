#include "../include/main.h"
#include "../include/pidController.h"

void init_PID(pidController *pid, float kP, float kI, float kD, float integralLimit){
	  pid->kP = kP;
	  pid->kI = kI;
	  pid->kD = kD;

	  pid->previousIntegral = 0;
	  pid->previousError = 0;
	  pid->integralLimit = integralLimit;

	  pid->previousTime = millis();
	  pid->out = 0;
}

void step_PID(pidController *pid, float current, float target){
	  unsigned currentTime = millis();
	  if (currentTime == pid->previousTime) return;
	  float error = target - current;
	  float P = pid->kP * error;
	  float I = (pid->kI * error * (currentTime - pid->previousTime)) + pid->previousIntegral;
	  float D = pid->kD * ((pid->previousError - error) / (currentTime - pid->previousTime));

	  if (I < -1 * pid->integralLimit) {
		    I = -1 * pid->integralLimit;
	  }
	  if (I > pid->integralLimit) {
		    I = pid->integralLimit;
	  }

	  pid->previousError = error;
	  pid->previousIntegral = I;
	  pid->previousTime = currentTime;

	  pid->out = P + I + D;

	  if (pid->out < -1.0) {
		    pid->out = -1.0;
	  }
	  if (pid->out > 1.0) {
		    pid->out = 1.0;
	  }
}

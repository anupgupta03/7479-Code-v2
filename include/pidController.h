
#ifndef SRC_PIDCONTROLLER_H_
#define SRC_PIDCONTROLLER_H_

typedef struct pidController_t {

	  float kP, kI, kD, previousIntegral, previousError, integralLimit;
	  unsigned previousTime;
	  float out;

} pidController;

void init_PID(pidController *pid, float kP, float kI, float kD, float integralLimit);
void step_PID(pidController *pid, float current, float target);


#endif //SRC_PIDCONTROLLER_H_

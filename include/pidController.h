/**
* @Date:   2016-11-22T21:31:49+11:00
* @Last modified time: 2016-11-23T11:37:41+11:00
*/
#ifndef SRC_PIDCONTROLLER_H_
#define SRC_PIDCONTROLLER_H_

/**
 * Struct to represent a PID controller
 * P - Bigger kP == smaller stopping distance
 * I - Bigger kI == harsher correction i.e. more power for lower error
 * D - Bigger kD == Reduces velocity
 * Bias - Minimum value for movement
 */
typedef struct pidController_t {
		// Constant of Proportion
	  float kP;
		// Constant of Integration
		float kI;
		// Constant of Derivation
		float kD;
		// Previous integral
		float previousIntegral;
		// Previous error
		float previousError;
		// Integral Limit
		float integralLimit;
		// Previous Time
	  unsigned previousTime;
		// Out Value
	  float out;
		// Output Bias
		float bias;
} pidController;

/**
 * Initializes a PID controller with constants and limits
 * @param pid           pidController to Init
 * @param kP            Constant of Proportion
 * @param kI            Constant of Integration
 * @param kD            Constant of Derivative
 * @param integralLimit Integral Limit
 */
void init_PID(pidController *pid, float kP, float kI, float kD, float integralLimit, float bias);
/**
 * Steps a PID controller through calculations
 * @param pid     pidController to step
 * @param current Current value
 * @param target  Target value
 */
void step_PID(pidController *pid, float current, float target);

#endif //SRC_PIDCONTROLLER_H_

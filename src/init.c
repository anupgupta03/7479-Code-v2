/**
 * @Date:   2016-10-22T14:32:24+11:00
* @Last modified time: 2016-12-02T22:47:47+11:00
 */
#include "../include/main.h"

// Main Variables Declaration
_Bool BASE_SLEW_CONTROL_ENABLED;
_Bool LIFT_SLEW_CONTROL_ENABLED;
Encoder enc_baseLeft, enc_baseRight, enc_liftLeft, enc_liftRight;
TaskHandle joyControlHandle, solControlHandle, odoTaskHandle, slewControlHandle, watchdogHandle;
OdometricLocalizer mainOdo;
Gyro mainGyro;
unsigned globalAutonFunction;

/**
 * Runs pre-initialization code.
 */
void initializeIO() {
	  /**
	   * Set pin modes for solenoids
	   */
	  pinMode(SOL_LEFT, OUTPUT);
	  pinMode(SOL_RIGHT, OUTPUT);
	  pinMode(SOL_FLIP, OUTPUT);
	  /**
	   * Assign default values to solenoids
	   */
	  digitalWrite(SOL_LEFT, 0);
	  digitalWrite(SOL_RIGHT, 0);
	  digitalWrite(SOL_FLIP, 0);
}

/**
 * Runs user initialization code.
 */
void initialize() {
	  /**
	   * Init LCD
	   */
	  lcdInit(LCD_PORT);
	  lcdClear(LCD_PORT);
	  lcdSetBacklight(LCD_PORT, true);

	  lcdPrint(LCD_PORT, 1, "  INITIALIZING  ");
	  lcdPrint(LCD_PORT, 2, " HILLCREST 7479 ");

	  /**
	   * Add motors to the slew handler
	   */
	  addMotor(MOTOR_LIFT_LEFT_BOT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_FRONT_LEFT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_FRONT_RIGHT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_LEFT_TOP, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_LEFT_MID, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_RIGHT_TOP, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_RIGHT_MID, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_BACK_RIGHT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_BACK_LEFT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_RIGHT_BOT, MOTOR_SLOW_SLEW_RATE);
	  /**
	   * Init Encoders
	   */
	  enc_baseRight = encoderInit(QUAD_BASE_LEFT, QUAD_BASE_LEFT_2, false);
	  enc_baseLeft = encoderInit(QUAD_BASE_RIGHT, QUAD_BASE_RIGHT_2, true);
	  enc_liftLeft = encoderInit(QUAD_LIFT_LEFT, QUAD_LIFT_LEFT_2, false);
	  enc_liftRight = encoderInit(QUAD_LIFT_RIGHT, QUAD_LIFT_RIGHT_2, false);

	  /**
	   * Init OdometricLocalizer
	   */
	  init_OdometricLocalizer(&mainOdo, enc_baseLeft, enc_baseRight, IDLE_WHEEL_DIAMETER, IDLE_TRACK_WIDTH, IDLE_COUNTS_PER_REVOLUTION);

	  /**
	   * Init Gyro
	   */
	  mainGyro = gyroInit(GYRO_PORT, 170);

	  /**
	   * Set default autonomous program
	   */
	  globalAutonFunction = FUNC_AUTON_RIGHT_PRIMARY;

	  return;
}

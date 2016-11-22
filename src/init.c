/**
 * File for initialization code.
 */

#include "../include/main.h"
int g_IntakeForkState;
_Bool BASE_SLEW_CONTROL_ENABLED;
_Bool LIFT_SLEW_CONTROL_ENABLED;
_Bool g_shouldResetSensors;
Encoder enc_baseLeft, enc_baseRight, enc_liftLeft, enc_liftRight;
TaskHandle joyControlHandle, solControlHandle, odoTaskHandle,  slewControlHandle;
OdometricLocalizer mainOdo;
Gyro mainGyro;
pidController headingPID, distancePID;

/**
 * Runs pre-initialization code.
 */
void initializeIO() {

	  pinMode(SOL_LEFT, OUTPUT);
	  pinMode(SOL_RIGHT, OUTPUT);

	  digitalWrite(SOL_LEFT, 0);
	  digitalWrite(SOL_RIGHT, 0);

	  g_IntakeForkState = 0;
}

/**
 * Runs user initialization code.
 */
void initialize() {

	  lcdInit(LCD_PORT);
	  lcdClear(LCD_PORT);
	  lcdSetBacklight(LCD_PORT, true);

	  lcdPrint(LCD_PORT, 1, " ROBOT STARTING ");
	  lcdPrint(LCD_PORT, 2, "  PLEASE WAIT   ");
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "DELEGATING SLEWS");
	  addMotor(MOTOR_BASE_FRONT_LEFT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_FRONT_RIGHT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_BACK_LEFT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_BASE_BACK_RIGHT, MOTOR_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_LEFT_TOP, LIFT_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_LEFT_BOT, LIFT_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);
	  addMotor(MOTOR_LIFT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);

	  lcdClear(LCD_PORT);


	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "ENC Init");
	  enc_baseRight = encoderInit(QUAD_BASE_LEFT, QUAD_BASE_LEFT_2, false);
	  enc_baseLeft = encoderInit(QUAD_BASE_RIGHT, QUAD_BASE_RIGHT_2, true);
	  enc_liftLeft = encoderInit(QUAD_LIFT_LEFT, QUAD_LIFT_LEFT_2, false);
	  enc_liftRight = encoderInit(QUAD_LIFT_RIGHT, QUAD_LIFT_RIGHT_2, false);
	  lcdPrint(LCD_PORT, 1, "ODO Init");
	  init_OdometricLocalizer(&mainOdo, Optical, enc_baseLeft, enc_baseRight, mainGyro, IDLE_WHEEL_DIAMETER, IDLE_TRACK_WIDTH, IDLE_COUNTS_PER_REVOLUTION);
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "ODO Reset");
	  encoderReset(enc_baseLeft);
	  encoderReset(enc_baseRight);
	  encoderReset(enc_liftLeft);
	  encoderReset(enc_liftRight);
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "GYRO Init");
	  mainGyro = gyroInit(GYRO_PORT, 170);
	  // gyroReset(mainGyro);
	  // delay(1000);
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "INIT Complete");

	  return;
}

/*
 * File for operator control code.
 */

#include "../include/main.h"



/*
 * Runs the user operator control code.
 */
void operatorControl() {
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "BEGIN Op.");

	  if (g_shouldResetSensors) {
		    encoderReset(enc_baseLeft);
		    encoderReset(enc_baseRight);
		    encoderReset(enc_liftLeft);
		    encoderReset(enc_liftRight);
		    delay(100);
	  }

	  LIFT_SLEW_CONTROL_ENABLED = true;
	  BASE_SLEW_CONTROL_ENABLED = true;

	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "START watchdog");

	  joyControlHandle = taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
	  solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	  odoTaskHandle = taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 3));
	  slewControlHandle = taskCreate(slewrateControl_task, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
	  taskCreate(watchDogManagement, 64, NULL, TASK_PRIORITY_DEFAULT);

	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, "op init complete");
	  lcdClear(LCD_PORT);
	  //  OdometricLocalizer *odoo = &mainOdo;
	  while (true) {

		    // if (taskGetState(watchdogHandle) == (TASK_DEAD || TASK_RUNNABLE)){
		    //   taskDelete(watchdogHandle);
		    //   taskCreate(watchDogManagement, 64, NULL, 1);
		    // }

		    // lcdPrint(LCD_PORT, 1, "Main: %1.2f%s", (double)powerLevelMain() / 1000.0,"V");
		    // lcdPrint(LCD_PORT, 2, "Backup: %1.2f%s",(double)powerLevelBackup() / 1000.0, "V");
		    // lcdPrint(LCD_PORT, 1, "%d", encoderGet(enc_baseLeft));
		    // lcdPrint(LCD_PORT, 2, "%d", encoderGet(enc_baseRight));
		    // lcdPrint(LCD_PORT, 1, "%d", gyroGet(mainGyro));
		    // if (mainGyro == NULL) lcdPrint(LCD_PORT, 2, "IS NULL");
		    lcdPrint(LCD_PORT, 1, "(%.2f, %.2f)", mainOdo.xPos, mainOdo.yPos);
		    lcdPrint(LCD_PORT, 2, "%f", mainOdo.heading);

		    delay(20);
	  }
}

/**
 * @Date:   2016-10-22T14:32:24+11:00
* @Last modified time: 2016-12-02T11:36:24+11:00
 */

#include "../include/main.h"
/*
 * Runs the user operator control code.
 */
void operatorControl() {

	  LIFT_SLEW_CONTROL_ENABLED = true;
	  BASE_SLEW_CONTROL_ENABLED = true;

	  joyControlHandle = taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
	  solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	  odoTaskHandle = taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 3));
	  slewControlHandle = taskCreate(slewrateControl_task, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
	  watchdogHandle = taskCreate(watchDogManagement, 64, NULL, TASK_PRIORITY_LOWEST + 1);

	  while (true) {
		    lcdPrint(LCD_PORT, 1, "Main: %d.%03d V", powerLevelMain() / 1000, powerLevelMain()%1000);
		    lcdPrint(LCD_PORT, 2, "Backup: %d.%03d V", powerLevelBackup() / 1000, powerLevelBackup()%1000);

		    // lcdPrint(LCD_PORT, 1, "%d", encoderGet(enc_baseLeft));
		    // lcdPrint(LCD_PORT, 2, "%d", encoderGet(enc_baseRight));
		    // lcdPrint(LCD_PORT, 1, "%d", gyroGet(mainGyro));
		    // lcdPrint(LCD_PORT, 1, "(%.2f, %.2f)", mainOdo.currentPosition.x, mainOdo.currentPosition.y);
		    // lcdPrint(LCD_PORT, 2, "%f", mainOdo.currentPosition.h);

		    delay(20);
	  }
}

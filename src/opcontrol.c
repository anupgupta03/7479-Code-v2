/**
 * @Date:   2016-10-22T14:32:24+11:00
* @Last modified time: 2016-12-02T21:02:41+11:00
 */

#include "../include/main.h"
/*
 * Runs the user operator control code.
 */
void operatorControl() {
	  mainMenuInit();
	  LIFT_SLEW_CONTROL_ENABLED = true;
	  BASE_SLEW_CONTROL_ENABLED = true;

	  startAllTasks();

	  while (true) {
		    lcdPrint(LCD_PORT, 1, "Main: %1.2f%s", (double)powerLevelMain() / 1000.0,"V");
		    lcdPrint(LCD_PORT, 2, "Backup: %1.2f%s",(double)powerLevelBackup() / 1000.0, "V");
		    // lcdPrint(LCD_PORT, 1, "%d", encoderGet(enc_baseLeft));
		    // lcdPrint(LCD_PORT, 2, "%d", encoderGet(enc_baseRight));
		    // lcdPrint(LCD_PORT, 1, "%d", gyroGet(mainGyro));
		    // lcdPrint(LCD_PORT, 1, "(%.2f, %.2f)", mainOdo.currentPosition.x, mainOdo.currentPosition.y);
		    // lcdPrint(LCD_PORT, 2, "%f", mainOdo.currentPosition.h);
		    delay(20);
	  }
}

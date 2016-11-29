/**
 * @Date:   2016-10-22T14:32:24+11:00
 * @Last modified time: 2016-11-23T11:35:31+11:00
 */

/*
 * File for autonomous code.
 */
#include "main.h"

void normalAutonomous(){
	  driveQuadPID(1200);
	  // turnTime(60, 230);
	  // delay(500);
	  // driveTime(127, 127, 1500);
	  // delay(1000);
	  // driveTime(-127, -127, 200);
	  // delay(250);
	  // turnTime(60, 250);
	  // driveTime(60, 60, 800);
	  // driveTime(-127, -127, 300);
	  // turnTime(60, 256.0);
	  // driveTime(127, 127, 600);
	  // driveTime(-127, -127, 400);
}

void programmingSkills() {
}

/*
 * Runs the user autonomous code.
 */
void autonomous() {
	  LIFT_SLEW_CONTROL_ENABLED = false;
	  BASE_SLEW_CONTROL_ENABLED = false;
	  normalAutonomous();
}

/**
 * @Date:   2016-10-22T14:32:24+11:00
* @Last modified time: 2016-12-02T22:22:50+11:00
 */

/*
 * File for autonomous code.
 */
#include "main.h"



void autonLeftPrimary(){

}

void autonRightPrimary() {

}

void programmingSkills(){

}

/*
 * Runs the user autonomous code.
 */
void autonomous() {
	  globalAutonFunction = FUNC_AUTON_LEFT_PRIMARY;
	  switch (globalAutonFunction) {
	  case FUNC_AUTON_LEFT_PRIMARY:
		    autonLeftPrimary();
		    break;
	  case FUNC_AUTON_RIGHT_PRIMARY:
		    autonRightPrimary();
		    break;
	  case FUNC_PROGRAMMING_SKILLS:
		    programmingSkills();
		    break;
	  }
}

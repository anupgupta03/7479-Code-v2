/**
 * @Date:   2016-10-23T13:39:38+11:00
* @Last modified time: 2016-11-23T11:36:01+11:00
 */
#include "../include/TaskManagement.h"
#include "../include/main.h"

void solenoidControlTask(void *ignore) {
	  while (true) {
		    if (joystickGetDigital(1, 8, JOY_RIGHT) == 1) {
			      toggleDigitalPort(SOL_LEFT);
			      toggleDigitalPort(SOL_RIGHT);
		    }
		    if (joystickGetDigital(1, 8, JOY_UP) == 1) {
			      toggleDigitalPort(SOL_FLIP);
		    }
		    delay(500);
	  }
}

void odoUpdateTask(void *ignore) {
	  while (true) {
		    step_OdometricLocalizer(&mainOdo);
		    delay(100);
	  }
}

void joystickControlTask(void *ignore) {
	  while (true) {
		    switch (DRIVE_TYPE) {
		    case false:
			      setDriveLeft(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_LV) + joystickGetAnalog(1, JOY_JOY_LH)));
			      setDriveRight(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_LV) - joystickGetAnalog(1, JOY_JOY_LH)));
			      break;

		    case true:
			      setDriveLeft(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_LV)));
			      setDriveRight(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_RV)));
			      break;
		    }

		    // Lift going up
		    if (joystickGetDigital(1, 5, JOY_UP) == 1 && joystickGetDigital(1, 5, JOY_DOWN) != 1 && joystickGetDigital(1, 6, JOY_UP) != 1) {
			      if (encoderGet(enc_liftLeft) < LIFT_UPPER_LIMIT) {
					setLift(127);
			      } else {
					setLift(0);
			      }
		    }

		    // Lift going down
		    if (joystickGetDigital(1, 5, JOY_UP) != 1 && joystickGetDigital(1, 5, JOY_DOWN) == 1 && joystickGetDigital(1, 6, JOY_UP) != 1) {
			      if (encoderGet(enc_liftLeft) > LIFT_LOWER_LIMIT) {
					setLift(-127);
			      } else {
					setLift(0);
			      }
		    }

		    // Lift up and hold
		    if (joystickGetDigital(1, 5, JOY_UP) != 1 && joystickGetDigital(1, 5, JOY_DOWN) != 1 && joystickGetDigital(1, 6, JOY_UP) == 1) {
			      if (encoderGet(enc_liftLeft) < LIFT_HALF_LIMIT) {
					setLift(127);
			      } else {
					setLift(0);
			      }
		    }

		    // Lift doing nothing
		    if (joystickGetDigital(1, 5, JOY_UP) != 1 && joystickGetDigital(1, 5, JOY_DOWN) != 1 && joystickGetDigital(1, 6, JOY_UP) != 1) {
			      setLift(0);
		    }

		    delay(20);
	  }
}

void watchDogManagement(void *ignore) {
	  do {
		    if ((taskGetState(joyControlHandle) == TASK_DEAD || taskGetState(joyControlHandle) == TASK_RUNNABLE) && taskGetState(joyControlHandle) != TASK_RUNNING) {
			      taskDelete(joyControlHandle);
			      joyControlHandle = taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
		    }
		    if ((taskGetState(solControlHandle) == TASK_DEAD || taskGetState(solControlHandle) == TASK_RUNNABLE) && taskGetState(solControlHandle) != TASK_RUNNING) {
			      taskDelete(solControlHandle);
			      solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
		    }
		    if ((taskGetState(odoTaskHandle) == TASK_DEAD || taskGetState(odoTaskHandle) == TASK_RUNNABLE) && taskGetState(odoTaskHandle) != TASK_RUNNING) {
			      taskDelete(odoTaskHandle);
			      odoTaskHandle = taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 3));
		    }
		    if ((taskGetState(slewControlHandle) == TASK_DEAD || taskGetState(slewControlHandle) == TASK_RUNNABLE) && taskGetState(slewControlHandle) != TASK_RUNNING) {
			      taskDelete(slewControlHandle);
			      slewControlHandle = taskCreate(slewrateControl_task, 1024, NULL, (TASK_PRIORITY_HIGHEST - 2));
		    }
		    delay(100);
	  } while (true);
}

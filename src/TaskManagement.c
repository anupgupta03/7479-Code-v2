#include "../include/main.h"
#include "../src/TaskManagement.h"

TaskHandle joyControlHandle, solControlHandle, odoTaskHandle, slewControlHandle;
Encoder enc_baseLeft, enc_baseRight, enc_liftLeft, enc_liftRight;
OdometricLocalizer mainOdo;

void solenoidControlTask(void *ignore) {
    while (true) {
        if (joystickGetDigital(1, 8, JOY_RIGHT) == 1) toggleIntakeForks();
        delay(500);
    }
}

void odoUpdateTask(void *ignore) {
    while (true) {
        step_OdometricLocalizer(&mainOdo);
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

        if (taskGetState(joyControlHandle) == (TASK_DEAD || TASK_RUNNABLE)) {
            taskDelete(joyControlHandle);
            joyControlHandle = taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
        }
        if (taskGetState(solControlHandle) == (TASK_DEAD || TASK_RUNNABLE)) {
            taskDelete(solControlHandle);
            solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        }
        if (taskGetState(odoTaskHandle) == (TASK_DEAD || TASK_RUNNABLE)) {
            taskDelete(odoTaskHandle);
            odoTaskHandle = taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 3));
        }
        if (taskGetState(slewControlHandle) == (TASK_DEAD || TASK_RUNNABLE)) {
            taskDelete(slewControlHandle);
            slewControlHandle = taskCreate(slewrateControl_task, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
        }
        delay(5000);
    } while (true);
}
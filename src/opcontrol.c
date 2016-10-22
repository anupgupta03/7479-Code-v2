/*
 * File for operator control code.
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 ********************************************************************************/

#include "main.h"
//#include "motorControlFunctions.h"

_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED, g_ShouldResetSensors;

TaskHandle joyControlHandle, solControlHandle, odoTaskHandle;

OdometricLocalizer mainOdo;
// uint8_t volatile * joyWatchDogFlag = (uint8_t volatile *)0x00;

/*
 * Waits for a value to be Zero before allowing a thread to continue
 */
void waitForZero(int value) {
    while (value != 0) {
        delay(20);
    }
}
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
            odoTaskHandle = taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 2));
        }
        delay(5000);
    } while (true);
}

/**
 * Runs the user operator control code.
 */
void operatorControl() {

    taskCreate(watchDogManagement, 64, NULL, 1);
// joyControlHandle = taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
// solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

    LIFT_SLEW_CONTROL_ENABLED = false;
    BASE_SLEW_CONTROL_ENABLED = false;

    lcdClear(LCD_PORT);

    while (true) {


        lcdPrint(LCD_PORT, 1, "Main: %1.2f%s", (double) powerLevelMain() / 1000.0, "V");
        lcdPrint(LCD_PORT, 2, "Backup: %1.2f%s", (double) powerLevelBackup() / 1000.0, "V");

        delay(20);
    }
}

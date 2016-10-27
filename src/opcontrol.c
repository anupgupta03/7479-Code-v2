/*
 * File for operator control code.
 *
 * This file should contain the user operatorControl() function and any
 * functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR
 *ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source
 * code may be obtained from http://sourceforge.net/projects/freertos/files/ or
 * on request.
 ********************************************************************************/

#include "../include/main.h"

_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED,
    g_ShouldResetSensors;
OdometricLocalizer mainOdo;

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
  joyControlHandle =
      taskCreate(joystickControlTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));
  solControlHandle = taskCreate(solenoidControlTask, TASK_DEFAULT_STACK_SIZE,
                                NULL, TASK_PRIORITY_DEFAULT);
  odoTaskHandle =
      taskCreate(odoUpdateTask, 1024, NULL, (TASK_PRIORITY_HIGHEST - 3));
  slewControlHandle =
      taskCreate(slewrateControl_task, 1024, NULL, (TASK_PRIORITY_HIGHEST - 1));

  taskCreate(watchDogManagement, 64, NULL, TASK_PRIORITY_DEFAULT);
  lcdClear(LCD_PORT);
  lcdPrint(LCD_PORT, 1, "op init complete");
  while (true) {

    // if (taskGetState(watchdogHandle) == (TASK_DEAD || TASK_RUNNABLE)){
    //   taskDelete(watchdogHandle);
    //   taskCreate(watchDogManagement, 64, NULL, 1);
    // }

    // lcdPrint(LCD_PORT, 1, "Main: %1.2f%s", (double)powerLevelMain() / 1000.0,
    //          "V");
    // lcdPrint(LCD_PORT, 2, "Backup: %1.2f%s",
    //          (double)powerLevelBackup() / 1000.0, "V");
    lcdPrint(LCD_PORT, 1, "%d", encoderGet(enc_liftLeft));
    lcdPrint(LCD_PORT, 2, "%d", encoderGet(enc_liftRight));
    delay(20);
  }
}

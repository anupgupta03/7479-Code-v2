/*
 * File for autonomous code.
 *
 * This file should contain the user autonomous() function and any functions related to it.
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

_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED, g_shouldResetSensors;

Encoder enc_baseLeft, enc_baseRight, enc_liftLeft, enc_liftRight;


void normalAutonomous(){
  int tt;
  turnTime(60, 230);
  delay(500);

  tt = encoderGet(enc_liftLeft);
  while (encoderGet(enc_liftLeft) < tt + 800)
      setLift(50);
  setLift(0);

  driveTime(127, 127, 1500);
  delay(1000);
  driveTime(-127, -127, 200);
  delay(250);
  turnTime(60, 250);
  driveTime(60, 60, 800);
  driveTime(-127, -127, 300);
  turnTime(60, 256.0);
  driveTime(127, 127, 600);
  driveTime(-127, -127, 400);

}

void programmingSkills() {

    // int tempEncoder, t22;
    // // Programming Skills
    // // -------------------------------------
    // driveTime(-60, -60, 300);
		//
    // tempEncoder = g_LiftLeftEncoder;
    // t22 = tempEncoder + 800;
		//
    // while (g_LiftLeftEncoder < tempEncoder + 800)
    //     setLift(127);
    // setLift(0);
    // toggleIntakeForks();
    // delay(500);
    // driveTime(60, 60, 300);
    // // Wait for preload
    // delay(2000);
    // // Drive back to fence
    // driveTime(-127, -127, 1250);
    // // Dump Cube
    // while (g_LiftLeftEncoder < LIFT_UPPER_LIMIT)
    //     setLift(127);
    // setLift(0);
    // // Lift down again
    // tempEncoder = g_LiftLeftEncoder;
    // while (g_LiftLeftEncoder > (LIFT_UPPER_LIMIT - t22) + 400)
    //     setLift(-50);
    // setLift(0);
		//
    // // Drive back to home
    // driveTime(127, 127, 800);
    // // Wait for preload
    // delay(2000);
		//
    // // Drive back to fence
    // driveTime(-127, -127, 1250);
    // // Dump Cube
    // while (g_LiftLeftEncoder < LIFT_UPPER_LIMIT)
    //     setLift(127);
    // setLift(0);
    // // Lift down again
    // tempEncoder = g_LiftLeftEncoder;
    // while (g_LiftLeftEncoder > (LIFT_UPPER_LIMIT - t22) + 400)
    //     setLift(-50);
    // setLift(0);
		//
    // // Drive back to home
    // driveTime(127, 127, 800);
    // // Wait for preload
    // delay(2000);
		//
    // // Drive back to fence
    // driveTime(-127, -127, 1250);
    // // Dump Cube
    // while (g_LiftLeftEncoder < LIFT_UPPER_LIMIT)
    //     setLift(127);
    // setLift(0);
    // // Lift down again
    // tempEncoder = g_LiftLeftEncoder;
    // while (g_LiftLeftEncoder > (LIFT_UPPER_LIMIT - t22) + 400)
    //     setLift(-50);
    // setLift(0);
		//
    // // Drive back to home
    // driveTime(127, 127, 800);
    // // Wait for preload
    // delay(2000);
		//
    // // Drive back to fence
    // driveTime(-127, -127, 1250);
    // // Dump Cube
    // while (g_LiftLeftEncoder < LIFT_UPPER_LIMIT)
    //     setLift(127);
    // setLift(0);
    // // Lift down again
    // tempEncoder = g_LiftLeftEncoder;
    // while (g_LiftLeftEncoder > (LIFT_UPPER_LIMIT - t22) + 400)
    //     setLift(-50);
    // setLift(0);
		//
    // // Drive back to home
    // driveTime(127, 127, 800);
    // // Wait for preload
    // delay(2000);
		//
    // // Drive back to fence
    // driveTime(-127, -127, 1250);
    // // Dump Cube
    // while (g_LiftLeftEncoder < LIFT_UPPER_LIMIT)
    //     setLift(127);
    // setLift(0);
    // // Lift down again
    // tempEncoder = g_LiftLeftEncoder;
    // while (g_LiftLeftEncoder > (LIFT_UPPER_LIMIT - t22) + 400)
    //     setLift(-50);
    // setLift(0);
		//
    // driveTime(127, 127, 500);
}

/*
 * Runs the user autonomous code.
 */
void autonomous() {

    LIFT_SLEW_CONTROL_ENABLED = false;
    BASE_SLEW_CONTROL_ENABLED = false;

//	programmingSkills();
	normalAutonomous();


    g_shouldResetSensors = false;
}

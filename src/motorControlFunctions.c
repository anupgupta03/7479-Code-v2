/*
 * motorControlFunctions.c
 *
 *  Created on: Sep 28, 2016
 *      Author: user
 */

#include "../include/main.h"
#include "../include/motorControlFunctions.h"

_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED;
int g_IntakeForkState;

void waitForZero(int value) {
        while (value != 0) delay(20);
}

float cJoyThreshold(int input) {
        return (abs(input) > JOYSTICK_THRESHOLD) ? (float)(mapCubic(input)) : 0.0;
}

void setIntakeForks(const int dir) {
        digitalWrite(SOL_LEFT, dir);
        digitalWrite(SOL_RIGHT, dir);
        g_IntakeForkState = dir;

}

void toggleIntakeForks() {
        digitalWrite(SOL_LEFT, digitalRead(SOL_LEFT) == 1 ? 0 : 1);
        digitalWrite(SOL_RIGHT, digitalRead(SOL_RIGHT) == 1 ? 0 : 1);
        g_IntakeForkState = (digitalRead(SOL_RIGHT) == 1 ? 0 : 1);

}

void setLiftLeft(const int power) {
        switch (LIFT_SLEW_CONTROL_ENABLED) {
        case true:
                setMotorSpeed(MOTOR_LIFT_LEFT_TOP, (-1 * power));
                setMotorSpeed(MOTOR_LIFT_LEFT_BOT, (-1 * power));
                break;
        case false:
                motorSet(MOTOR_LIFT_LEFT_TOP, (-1 * power));
                motorSet(MOTOR_LIFT_LEFT_BOT, (-1 * power));
                break;
        }

}

void setLiftRight(const int power) {
        switch (LIFT_SLEW_CONTROL_ENABLED) {
        case true:
                setMotorSpeed(MOTOR_LFIT_RIGHT_TOP, power);
                setMotorSpeed(MOTOR_LIFT_RIGHT_TOP, power);
                break;
        case false:
                motorSet(MOTOR_LFIT_RIGHT_TOP, power);
                motorSet(MOTOR_LIFT_RIGHT_TOP, power);
                break;
        }

}

void setDriveLeft(const int power) {
        switch (BASE_SLEW_CONTROL_ENABLED) {
        case true:
                setMotorSpeed(MOTOR_BASE_FRONT_LEFT, power);
                setMotorSpeed(MOTOR_BASE_BACK_LEFT, power);
                break;
        case false:
                motorSet(MOTOR_BASE_FRONT_LEFT, power);
                motorSet(MOTOR_BASE_BACK_LEFT, power);
                break;
        }

}

void setDriveRight(const int power) {
        switch (BASE_SLEW_CONTROL_ENABLED) {
        case true:
                setMotorSpeed(MOTOR_BASE_FRONT_RIGHT, -1 * power);
                setMotorSpeed(MOTOR_BASE_BACK_RIGHT, -1 * power);
                break;
        case false:
                motorSet(MOTOR_BASE_FRONT_RIGHT, -1 * power);
                motorSet(MOTOR_BASE_BACK_RIGHT, -1 * power);
                break;
        }

}

void setLift(const int power) {
        setLiftLeft(-1 * power);
        setLiftRight(-1 * (power + (sign(abs(encoderGet(enc_liftLeft)) - abs(encoderGet(enc_liftRight))) * power * 0.1)));

}

void driveTime(const int l_power, const int r_power, const int timeMs) {
        unsigned int startingTime = millis();
        while (startingTime + timeMs > millis()) {
                setDriveLeft(l_power);
                setDriveRight(r_power);
        }
        setDriveLeft(0);
        setDriveRight(0);
}

void driveStraightTime(const int power, const unsigned timeMs) {
        int initialLeft, initialRight, startingTime;
        initialLeft = encoderGet(enc_baseLeft);
        initialRight = encoderGet(enc_baseRight);
        startingTime = millis();

        // Drive at full power for 80% of ticks
        while (startingTime + (timeMs * 0.8) > millis()) {
                setDriveLeft(power);
                setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
                delay(20);
        }
        startingTime = millis();
        // Drive at 1/3 Power for remaining 20% of ticks
        while (startingTime + (timeMs * 0.2) > millis()) {
                setDriveLeft((power / 3));
                setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
                delay(20);
        }
        // Stop
        driveTime(-1 * (power / 2), -1 * (power / 2), 100);
        setDriveLeft(0);
        setDriveRight(0);

}

void turnTime(const int power, const int timeMs) {
        unsigned int startingTime = millis();
        while (startingTime + timeMs > millis()) {
                setDriveLeft(-1 * power);
                setDriveRight(power);
        }
        setDriveLeft(0.5 * power);
        setDriveRight(-0.5 * power);
        delay(75);
        setDriveRight(0);
        setDriveLeft(0);

}

void driveQuad(const int power, const int ticks) {
        int initialLeft, initialRight;
        initialLeft = encoderGet(enc_baseLeft);
        initialRight = encoderGet(enc_baseRight);
        // Drive at full power for 80% of ticks
        while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.8)) {
                setDriveLeft(power);
                setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
                delay(20);
        }
        // Drive at 1/3 Power for remaining 20% of ticks
        while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.2)) {
                setDriveLeft((power / 3));
                setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
                delay(20);
        }
        // Stop
        driveTime(-1 * (power / 2), -1 * (power / 2), 100);
        setDriveLeft(0);
        setDriveRight(0);

}

void turnQuad(const int power, const int ticks) {
        int initialLeft, initialRight;
        initialLeft = encoderGet(enc_baseLeft);
        initialRight = encoderGet(enc_baseRight);

        while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.6)) {
                setDriveLeft(-1 * power);
                setDriveRight(power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1));
                delay(20);
        }

        while (encoderGet(enc_baseLeft) < initialLeft + (ticks * 0.4)) {
                setDriveLeft((-1 * power / 3));
                setDriveRight((power + (sign(((encoderGet(enc_baseLeft) - initialLeft) - (encoderGet(enc_baseRight) - initialRight))) * power * 0.1)) / 3);
                delay(20);
        }
        //Drive
        turnTime(-1 * (power / 2), 100);
        setDriveLeft(0);
        setDriveRight(0);

}

void turnGyro(const int power, const int deg) {

// TODO: FINISH THIS FUNCTION

}

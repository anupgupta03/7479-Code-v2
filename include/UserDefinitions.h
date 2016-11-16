/*
 * UserDefinitions.h
 *
 *  Created on: Oct 4, 2016
 *      Author: natty
 */

#ifndef SRC_USERDEFINITIONS_H_
#define SRC_USERDEFINITIONS_H_

// Math
#include <math.h>

// Fast non-branching sign function
#define sign(x) (x > 0) - (x < 0)

#define PI 3.1415926535

#define half(v) ((v) / 2.0)
#define square(v) ((v) * (v))
#define cube(v) ((v) * (v) * (v))
#define cubeRoot(v) (pow(v, (1 / 3)))
#define inchesToTicks(i, d) (((i) / (PI * (d))) * 360)
#define ticksToInches(t, d) (((d)*PI) * ((t) / 360))
#define inchToCm(i) (i * 2.54)
#define cmToInch(i) (i / 2.54)

#define radToDeg(i) (i * (180 / PI))
#define degToRad(i) (i * (PI / 180))

#define mapCubic(i) ((2 * cube(i)) / 48387) + (i / 3)

#define DRIVE_ENABLED true
#define LIFT_ENABLED true
#define LOCALIZER_ENABLED false

#define LOW_TICKS_PER_REV 627.2
#define HIGH_TICKS_PER_REV 392
#define TURBO_TICKS_PER_REV 216.333

#define LIFT_UPPER_LIMIT 680
#define LIFT_HALF_LIMIT 250
#define LIFT_LOWER_LIMIT -5

// Number of sensor counts per single revolution of Idle wheels
#define IDLE_COUNTS_PER_REVOLUTION 360.0
// Diameter of Idler wheels
#define IDLE_WHEEL_DIAMETER 2.75
// Track width of Idler wheels
#define IDLE_TRACK_WIDTH 4.5

// Method of driving using the joysticks
// true = TANK DRIVE
// false = ARCADE DRIVE
#define DRIVE_TYPE true

#define JOYSTICK_THRESHOLD 10

// Motor Defines
#define MOTOR_BASE_FRONT_LEFT 2
#define MOTOR_BASE_FRONT_RIGHT 3 // Reversed
#define MOTOR_LIFT_LEFT_TOP 4
#define MOTOR_LIFT_LEFT_BOT 5
#define MOTOR_LIFT_RIGHT_TOP 6  // Reversed
#define MOTOR_LIFT_RIGHT_BOT 7  // Reversed
#define MOTOR_BASE_BACK_RIGHT 8 // Reversed
#define MOTOR_BASE_BACK_LEFT 9

// Solenoid Ports (Digital)
#define SOL_LEFT 1
#define SOL_RIGHT 2

// Optical Encoder Defines (Digital)
#define QUAD_BASE_LEFT 3
#define QUAD_BASE_LEFT_2 4

#define QUAD_BASE_RIGHT 5
#define QUAD_BASE_RIGHT_2 6

#define QUAD_LIFT_LEFT 7
#define QUAD_LIFT_LEFT_2 8

#define QUAD_LIFT_RIGHT 9
#define QUAD_LIFT_RIGHT_2 11

// Joystick Defines
#define JOY_JOY_LV 3
#define JOY_JOY_LH 4
#define JOY_JOY_RV 2
#define JOY_JOY_RH 1
#define JOY_BTN_LEFT 7
#define JOY_BTN_RIGHT 8
#define JOY_TRIG_LEFT 5
#define JOY_TRIG_RIGHT 6

// LCD Port
#define LCD_PORT uart1

// Gyro Port (Analog)
#define GYRO_PORT 1

typedef enum t_Direction { LEFT, RIGHT } Direction;

#endif /* SRC_USERDEFINITIONS_H_ */

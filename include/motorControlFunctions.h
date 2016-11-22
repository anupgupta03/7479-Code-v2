#ifndef MOTORCONTROLFUNCTIONS_H_INCLUDED
#define MOTORCONTROLFUNCTIONS_H_INCLUDED
#include "../include/UserDefinitions.h"

/**
 * Returns the Euclidian Distance between two points
 * @param  x1 First X-Coordinate
 * @param  y1 First Y-Coordinate
 * @param  x2 Second X-Coordinate
 * @param  y2 Second Y-Coordinate
 * @return    Euclidian Distance
 */
float eDist(int x1, int y1, int x2, int y2);
/**
 * Returns Degrees from position to another
 * @param  posFrom Starting Pos
 * @param  posTo   Finishing Pos
 * @return         Degrees to pos
 */
float dHeading(pos posFrom, pos posTo);
/**
 * Wait for a value to reach zero before allowing the thread to continue
 * @param value Value to watch
 */
void waitForZero(int *value);
/**
 * Calculates a Joystick threshold value and maps it to a cubic function
 * @param  input Input joystick Value
 * @return       Output Cubic or 0.0 if inside deadzone
 */
float cJoyThreshold(int input);
/**
 * Sets the state of the intake forks
 * @param dir Direction that the intake forks will be set to 0 = UP, 1 = DOWN
 */
void setIntakeForks(const int dir);
/**
 * Toggles the state of the intake forks
 */
void toggleIntakeForks();
/**
 * Sets the left side of the lift to a power
 * @param power Power to set the lift side to
 */
void setLiftLeft(const int power);
/**
 * Sets the right side of the lift to a power
 * @param power Power to set the lift side to
 */
void setLiftRight(const int power);
/**
 * Ssets the left side of the drive to a power
 * @param power Power to set the drive side to
 */
void setDriveLeft(const int power);
/**
 * Sets the right side of the drive to a power
 * @param power Power to set the drive side to
 */
void setDriveRight(const int power);
/**
 * Sets the entire lift to a power and keeps the sides equal with encoders
 * @param power Power to set the lift to
 */
void setLift(const int power);
/**
 * Drives for a specific time using raw motor control
 * @param l_power Power sent to the left side
 * @param r_power Power sent to the right side
 * @param timeMs  Time to drive for
 */
void driveTime(const int l_power, const int r_power, const int timeMs);
/**
 * Drives straight for a certain time using encoders to keep straight
 * @param power  Power sent to the drive
 * @param timeMs Time to drive
 */
void driveStraightTime(const int power, const unsigned timeMs);
/**
 * Turns using no encoders for a specified amount of time
 * @param power  Power sent to the drive
 * @param timeMs Time to drive
 */
void turnTime(const int power, const int timeMs);
/**
 * Turns using the gyro sensor
 * @param power Max power sent to the drive
 * @param deg   Number of degrees to turn
 */
void turnGyro(const int power, const int deg);
/**
 * Drives straight using encoders for a specified number of ticks
 * @param power Power sent to the drive
 * @param ticks Number of ticks to drive
 */
void driveQuad(const int power, const int ticks);
/**
 * Turns using encoders for a specified number of ticks
 * @param power Power sent to the drive
 * @param ticks Number of ticks to turn
 */
void turnQuad(const int power, const int ticks);

#endif //MOTORCONTROLFUNCTIONS_H_INCLUDED

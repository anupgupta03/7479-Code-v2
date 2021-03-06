/**
* @Date:   2016-10-22T14:32:57+11:00
* @Last modified time: 2016-12-02T20:54:40+11:00
*/



#ifndef MOTORCONTROLFUNCTIONS_H_INCLUDED
#define MOTORCONTROLFUNCTIONS_H_INCLUDED
#include "../include/OdometricLocalizer.h"
#include "../include/UserDefinitions.h"

/**
 * Returns the Euclidian Distance between two points
 * @param  posFrom First X-Coordinate
 * @param  posTo Second Y-Coordinate
 * @return    Euclidian Distance between points
 */
float eDist(pos posFrom, pos posTo);
/**
 * Returns Degrees from position to another
 * @param  posFrom Starting Pos
 * @param  posTo   Finishing Pos
 * @return         Degrees to pos
 */
float dHeading(pos posFrom, pos posTo);
/**
 * Finds smallest angle to target
 * @param  angle Input angle
 * @return       Output angle
 */
int fixAngle(int angle);
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
 * Toggles the state of a digital port
 * @param port Port number to toggle
 */
void toggleDigitalPort(unsigned port);
/**
 * Starts all tasks and assigns their handles
 */
void startAllTasks();
/**
 * Resets all Sensors to Zero
 */
void resetSensors();
/**
 * Resets all tasks and clears all values and variables
 */
void resetFunctionality();
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
void driveQuadPID(const int ticks);
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
/**
 * Moves the robot to a position based on a PID and OdometricLocalizer
 * @param odo  OdometricLocalizer object to read current position from
 * @param xPos Target X Position
 * @param yPos Target Y Position
 */
void moveToPosition(OdometricLocalizer *odo, float xPos, float yPos);

#endif //MOTORCONTROLFUNCTIONS_H_INCLUDED

/**
* @Date:   2016-10-22T14:32:57+11:00
* @Last modified time: 2016-11-23T11:28:39+11:00
*/
#ifndef ODOMETRICLOCALIZER_H_INCLUDED
#define ODOMETRICLOCALIZER_H_INCLUDED

#include <API.h>
#include "../include/main.h"
// Math helpers
#define radToDeg(i) ((i) * (180 / PI))
#define degToRad(i) ((i) * (PI / 180))

/**
 * Struct to represent a position of a robot
 */
typedef struct pos_t {
	  float x;
	  float y;
	  float h;
} pos;

/**
 * Struct to represent an OdometricLocalizer
 */
typedef struct t_OdometricLocalizer {
	  // Previous Encoder Counts
	  int previousLeftCounts;
	  int previousRightCounts;
	  int previousGyroHeading;
	  // Sensors attached to the axis of revolution
	  Encoder leftEncoder;
	  Encoder rightEncoder;
	  // Distance travelled per count (inches)
	  float distancePerCount;
	  // Radians per encoder count
	  float radiansPerCount;
	  //Current Position
	  pos currentPosition;
	// float x;
	// float y;
	// float h;
} OdometricLocalizer;

/**
 * Changes current position of an OdometricLocalizer object
 * @param odo  OdometricLocalizer object to modify
 * @param newX New X position to store
 * @param newY New Y position to store
 * @param newH New heading to store
 */
void setPos(OdometricLocalizer *odo, float newX, float newY, float newH);

/**
 * Initializes an OdometricLocalizer with provided parameters and does init math
 * @param odo                 OdometricLocalizer object to init
 * @param type                Type of encoder being used
 * @param leftEncoder         Encoder object for the left side of the drivetrain
 * @param rightEncoder        Encoder object for the right side of the drivetrain
 * @param wheelDiameter       Diameter of wheels
 * @param trackWidth          Distance between centers of wheels
 * @param countsPerRevolution Number of encoder counts per revolution
 */
void init_OdometricLocalizer(OdometricLocalizer *odo, Encoder leftEncoder, Encoder rightEncoder, float wheelDiameter,  float trackWidth, float countsPerRevolution);

/**
 * Steps an OdometricLocalizer through calculations
 * @param odo OdometricLocalizer to step through
 */
void step_OdometricLocalizer(OdometricLocalizer *odo);

#endif //ODOMETRICLOCALIZER_H_INCLUDED

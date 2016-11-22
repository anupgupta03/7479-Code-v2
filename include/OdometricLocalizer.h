#ifndef ODOMETRICLOCALIZER_H_INCLUDED
#define ODOMETRICLOCALIZER_H_INCLUDED
#include <API.h>
#include "../include/main.h"

/**
 * Enum for different types of encoders
 */
typedef enum t_EncoderTypes { IME, Optical } EncoderTypes;

/**
 * Struct to represent an OdometricLocalizer for a robot
 */
typedef struct t_OdometricLocalizer {
	  // Type of encoder being measured
	  EncoderTypes encoderType;
	  // Previous Encoder Counts
	  int previousLeftCounts;
	  int previousRightCounts;
	  int previousGyroHeading;
	  // Sensors attached to the axis of revolution
	  Encoder leftEncoder;
	  Encoder rightEncoder;
	  Gyro gyro;
	  // Distance travelled per count (inches)
	  float distancePerCount;
	  // Radians per encoder count
	  float radiansPerCount;
	  // Current X Coordinate
	  float xPos;
	  // Current Y Coordinate
	  float yPos;
	  // Current Heading
	  float heading;

} OdometricLocalizer;

/**
 * Changes current position of an OdometricLocalizer object
 * @param odo  OdometricLocalizer object to modify
 * @param newX New X position to store
 * @param newY New Y position to store
 * @param newH New heading to store
 */
void changePos(OdometricLocalizer *odo, float newX, float newY, float newH);

/**
 * Get encoder reading based on OdometricLocalizer Parameters
 * @param  odo  OdometricLocalizer to modify
 * @param  side Drive side to retrieve encoder values from
 * @return      Encoder value requested
 */
int getEncoderReading(OdometricLocalizer *odo, Direction side);

/**
 * Initializes an OdometricLocalizer with provided parameters and does init math
 * @param odo                 OdometricLocalizer object to init
 * @param type                Type of encoder being used
 * @param leftEncoder         Encoder object for the left side of the drivetrain
 * @param rightEncoder        Encoder object for the right side of the drivetrain
 * @param gyro                Gyro object for rotational measurement
 * @param wheelDiameter       Diameter of wheels
 * @param trackWidth          Distance between centers of wheels
 * @param countsPerRevolution Number of encoder counts per revolution
 */
void init_OdometricLocalizer(OdometricLocalizer *odo, EncoderTypes type, Encoder leftEncoder, Encoder rightEncoder, Gyro gyro, float wheelDiameter,  float trackWidth, float countsPerRevolution);

/**
 * Steps an OdometricLocalizer through calculations
 * @param odo OdometricLocalizer to step through
 */
void step_OdometricLocalizer(OdometricLocalizer *odo);

#endif //ODOMETRICLOCALIZER_H_INCLUDED

/**
 * @Date:   2016-10-22T14:32:57+11:00
 * @Last modified time: 2016-11-23T11:35:43+11:00
 */

#include "../include/main.h"
#include "../include/OdometricLocalizer.h"

void setPos(OdometricLocalizer *odo, float newX, float newY, float newH) {
	  odo->currentPosition.x = newX;
	  odo->currentPosition.y = newY;
	  odo->currentPosition.h = newH;
}

void init_OdometricLocalizer(OdometricLocalizer *odo, Encoder leftEncoder, Encoder rightEncoder, float wheelDiameter,  float trackWidth, float countsPerRevolution) {
	  // Set encoders to be used
	  odo->leftEncoder = leftEncoder;
	  odo->rightEncoder = rightEncoder;
	  // Calculate distance travelled per count
	  odo->distancePerCount = (PI * wheelDiameter) / countsPerRevolution;
	  // Calculate radians travelled per count
	  odo->radiansPerCount = (PI * (wheelDiameter / trackWidth)) / countsPerRevolution;
	  // Set position to 0,0,90
	  setPos(odo, 0, 0, 90);
	  // Set previous counts
	  odo->previousLeftCounts = encoderGet(odo->leftEncoder);
	  odo->previousRightCounts = encoderGet(odo->rightEncoder);
}

void step_OdometricLocalizer(OdometricLocalizer *odo) {
	  // Variables to store left and right counts
	  int leftCounts = encoderGet(odo->leftEncoder);
	  int rightCounts = encoderGet(odo->rightEncoder);
	  // Calculate change in Left side
	  int dLeftCounts = leftCounts - odo->previousLeftCounts;
	  // Calculate change in Right side
	  int dRightCounts = rightCounts - odo->previousRightCounts;
	  //Return if insignificant
	  if (dLeftCounts < 2 && dRightCounts < 2) return;
	  // Calcualte change in distance travelled
	  float dDistance = 0.5 * (float)(dLeftCounts + dRightCounts) * odo->distancePerCount;
	  // Calculate change in heading
	  float dH = radToDeg((float)(dRightCounts - dLeftCounts) * odo->radiansPerCount);
	  // Calculate change in X position
	  float dX = dDistance * (float)cos(odo->currentPosition.h + (0.5 * dH));
	  // Calcualte change in Y position
	  float dY = dDistance * (float)sin(odo->currentPosition.h + (0.5 * dH));
	  // Add each change
	  odo->currentPosition.x += dX;
	  odo->currentPosition.y += dY;
	  odo->currentPosition.h += dH;
	  // Limit heading to [-PI, PI)
	  if (odo->currentPosition.h < 0.0) {
		    odo->currentPosition.h += 360.0;
	  }
	  if (odo->currentPosition.h > 359) {
		    odo->currentPosition.h -= 360;
	  }
	  // Set previous counts to initial counts
	  odo->previousLeftCounts = leftCounts;
	  odo->previousRightCounts = rightCounts;
}

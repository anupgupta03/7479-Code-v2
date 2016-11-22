#include "../include/main.h"

#include "../include/OdometricLocalizer.h"


void changePos(OdometricLocalizer *odo, float newX, float newY, float newH) {
	  odo->currentPosition.x = newX;
	  odo->currentPosition.y = newY;
	  odo->currentPosition.h = newH;
}

void init_OdometricLocalizer(OdometricLocalizer *odo, EncoderTypes type, Encoder leftEncoder, Encoder rightEncoder, Gyro gyro, float wheelDiameter,  float trackWidth, float countsPerRevolution) {
	  // Set encoder type being used
	  odo->encoderType = type;

	  odo->leftEncoder = leftEncoder;
	  odo->rightEncoder = rightEncoder;

	  // Calculate distance travelled per count
	  odo->distancePerCount = (PI * wheelDiameter) / countsPerRevolution;
	  // Calculate radians travelled per count
	  odo->radiansPerCount = (PI * (wheelDiameter / trackWidth)) / countsPerRevolution;
	  // Set position to 0,0,90
	  changePos(odo, 0, 0, 90);
	  // Set previous counts
	  odo->previousLeftCounts = encoderGet(odo->leftEncoder);
	  odo->previousRightCounts = encoderGet(odo->rightEncoder);
	  odo->previousGyroHeading = gyroGet(odo->gyro);
}

void step_OdometricLocalizer(OdometricLocalizer *odo) {
	  // Variables to store left and right counts
	  int leftCounts = encoderGet(odo->leftEncoder);
	  int rightCounts = encoderGet(odo->rightEncoder);

	  // Calculate change in Left side
	  int dLeftCounts = leftCounts - odo->previousLeftCounts;
	  // Calculate change in Right side
	  int dRightCounts = rightCounts - odo->previousRightCounts;
	  if (dLeftCounts < 2 && dRightCounts < 2) return;
	  // Calcualte change in distance travelled
	  float dDistance = 0.5 * (float)(dLeftCounts + dRightCounts) * odo->distancePerCount;
	  // Calculate change in heading
	  float dH = (float)(dRightCounts - dLeftCounts) * odo->radiansPerCount * (180.0/PI);
	  // GYRO: float dH = gyroCounts - odo->previousGyroHeading;
	  // Calculate change in X position
	  float dX = dDistance * (float)cos(odo->currentPosition.h + (0.5 * dH));
	  // Calcualte change in Y position
	  float dY = dDistance * (float)sin(odo->currentPosition.h + (0.5 * dH));

	  // Add each change
	  odo->currentPosition.x += dX;
	  odo->currentPosition.y += dY;
	  odo->currentPosition.h += dH;

	  // Limit heading to [-PI, PI)
	  if (odo->currentPosition.h > 180.0) {
		    odo->currentPosition.h -= (2 * 180.0);
	  } else if (odo->currentPosition.h <= (-1 * 180.0)) {
		    odo->currentPosition.h += (2 * 180.0);
	  }
	  // Set previous counts to initial counts
	  odo->previousLeftCounts = leftCounts;
	  odo->previousRightCounts = rightCounts;
	  // odo->previousGyroHeading = gyroCounts;
}

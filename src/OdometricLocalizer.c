#include "../include/main.h"

#include "../include/OdometricLocalizer.h"


void changePos(OdometricLocalizer *odo, float newX, float newY, float newH) {
	  odo->xPos = newX;
	  odo->yPos = newY;
	  odo->heading = newH;
}

int getEncoderReading(OdometricLocalizer *odo, Direction side) {
	  switch (odo->encoderType) {
	  case IME:
		    return NULL;
		    break;
	  case Optical:
		    switch (side) {
		    case (LEFT):
			      return encoderGet(odo->leftEncoder);
			      break;
		    case (RIGHT):
			      return encoderGet(odo->rightEncoder);
			      break;
		    }
		    break;
	  }
	  return NULL;
}

void init_OdometricLocalizer(OdometricLocalizer *odo, EncoderTypes type, Encoder *leftEncoder, Encoder *rightEncoder, Gyro *gyro, float wheelDiameter,  float trackWidth, float countsPerRevolution) {
	  // Set encoder type being used
	  odo->encoderType = type;

	  odo->leftEncoder = leftEncoder;
	  odo->rightEncoder = rightEncoder;
	  odo->gyro = gyro;

	  // Calculate distance travelled per count
	  odo->distancePerCount = (PI * wheelDiameter) / countsPerRevolution;
	  // Calculate radians travelled per count
	  odo->radiansPerCount = (PI * (wheelDiameter / trackWidth)) / countsPerRevolution;
	  // Set position to 0,0,90
	  changePos(odo, 0, 0, degToRad(90));
	  // Set previous counts
	  odo->previousLeftCounts = getEncoderReading(odo, LEFT);
	  odo->previousRightCounts = getEncoderReading(odo, RIGHT);
	  odo->previousGyroHeading = gyroGet(odo->gyro);
}

void step_OdometricLocalizer(OdometricLocalizer *odo) {
	  // Variables to store left and right counts
	  int leftCounts = getEncoderReading(odo, LEFT);
	  int rightCounts = getEncoderReading(odo, RIGHT);
	  int gyroCounts = gyroGet(odo->gyro);

	  // If movement is negligble
	  if (abs(leftCounts - odo->previousLeftCounts) < 2 || abs(rightCounts - odo->previousRightCounts) < 2) return;

	  // Calcualte change in distance travelled
	  float dDistance = 0.5 * (float)((leftCounts - odo->previousLeftCounts) + (rightCounts - odo->previousRightCounts)) * odo->distancePerCount;
	  // Calculate change in heading
	  float dH = gyroCounts - odo->previousGyroHeading;
	  // Calculate change in X position
	  float dX = dDistance * (float)cos(odo->heading + (0.5 * dH));
	  // Calcualte change in Y position
	  float dY = dDistance * (float)sin(odo->heading + (0.5 * dH));

	  // Add each change
	  odo->xPos += dX;
	  odo->yPos += dY;
	  odo->heading += dH;

	  // Limit heading to [-PI, PI)
	  if (odo->heading > 180.0) {
		    odo->heading -= (2 * 180.0);
	  } else if (odo->heading <= (-1 * 180.0)) {
		    odo->heading += (2 * 180.0);
	  }
	  // Set previous counts to initial counts
	  odo->previousLeftCounts = leftCounts;
	  odo->previousRightCounts = rightCounts;
	  odo->previousGyroHeading = gyroCounts;
}

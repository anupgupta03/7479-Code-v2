#include "main.h"

#include "../src/OdometricLocalizer.h"


void getOdoPosition(OdometricLocalizer *odo, Pose *pos) {
    pos->x = odo->xPos;
    pos->y = odo->yPos;
    pos->h = odo->heading;

}

// Changes current position of an OdometricLocalizer object
void changePos(OdometricLocalizer *odo, float newX, float newY, float newH) {
    odo->xPos = newX;
    odo->yPos = newY;
    odo->heading = newH;
}

int getEncoderReading(OdometricLocalizer *odo, Direction side) {

    // int tempEncoderValue = 0;

    switch (odo->encoderType) {

    case IME:
        return NULL;
        // switch (side) {
        // case (LEFT):
        // 	imeGet(odo->LeftEncoder_port, &tempEncoderValue);
        // 	if (odo->leftFlip) {
        // 		return -1 * tempEncoderValue;
        // 	} else {
        // 		return tempEncoderValue;
        // 	}
        // 	break;
        //
        // case (RIGHT):
        // 	imeGet(odo->RightEncoder_port, &tempEncoderValue);
        // 	if (odo->rightFlip) {
        // 		return -1 * tempEncoderValue;
        // 	} else {
        // 		return tempEncoderValue;
        // 	}
        // 	break;
        // }
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

// Initializes an OdometricLocalizer with provided parameters and does init math
int init_OdometricLocalizer(OdometricLocalizer *odo, EncoderTypes type, float wheelDiameter,	float trackWidth, float countsPerRevolution) {

    // Set encoder type being used
    odo->encoderType = type;

    // Calculate distance travelled per count
    odo->distancePerCount = (PI * wheelDiameter) / countsPerRevolution;
    // Calculate radians travelled per count
    odo->radiansPerCount = (PI * (wheelDiameter / trackWidth))
                           / countsPerRevolution;

    // Set position to 0,0,90
    changePos(odo, 0, 0, degToRad(90));

    odo->previousLeftCounts = getEncoderReading(odo, LEFT);
    odo->previousRightCounts = getEncoderReading(odo, RIGHT);

    return 0;
}

// Steps an OdometricLocalizer through calculations
void step_OdometricLocalizer(OdometricLocalizer *odo) {
    // Variables to store left and right counts
    int leftCounts = getEncoderReading(odo, LEFT);

    int rightCounts = getEncoderReading(odo, RIGHT);

    // If movement is negligble
    if (abs(leftCounts - odo->previousLeftCounts) < 2	|| abs(rightCounts - odo->previousRightCounts) < 2) return;

    // Calculate change in Left side
    int dLeftCounts = leftCounts - odo->previousLeftCounts;
    // Calculate change in Right side
    int dRightCounts = rightCounts - odo->previousRightCounts;

    // Calcualte change in distance travelled
    float dDistance = 0.5 * (float) (dLeftCounts + dRightCounts) * odo->distancePerCount;
    // Calculate change in heading
    float dH = (float) (dRightCounts - dLeftCounts) * odo->radiansPerCount;
    // Calculate change in X position
    float dX = dDistance * (float) cos(odo->heading + (0.5 * dH));
    // Calcualte change in Y position
    float dY = dDistance * (float) sin(odo->heading + (0.5 * dH));

    // Add each change
    odo->xPos += dX;
    odo->yPos += dY;
    odo->heading += dH;

    // Limit heading to [-PI, PI)
    if (odo->heading > PI) {
        odo->heading -= (2 * PI);
    } else if (odo->heading <= (-1 * PI)) {
        odo->heading += (2 * PI);
    }

    // Set previous counts to initial counts
    odo->previousLeftCounts = leftCounts;
    odo->previousRightCounts = rightCounts;
}

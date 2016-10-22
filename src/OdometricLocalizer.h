#ifndef ODOMETRICLOCALIZER_H_INCLUDED
#define ODOMETRICLOCALIZER_H_INCLUDED

// Types of encoders that can be used
typedef enum t_EncoderTypes {
	IME, Optical
} EncoderTypes;

// Position struct
typedef struct t_Pose {
	// X-Coordinate
	float x;
	// Y-Coordinate
	float y;
	// Heading
	float h;
} Pose;

typedef struct t_OdometricLocalizer {
	// Type of encoder being measured
	EncoderTypes encoderType;

	// Previous Encoder Counts
	int previousLeftCounts;
	int previousRightCounts;

	// Sensors attached to the axle of revolution
	int LeftEncoder_port;
	int RightEncoder_port;

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

	bool leftFlip;
	bool rightFlip;

} OdometricLocalizer;

// Returns a Pose object containing information from a provided OdometricLocalizer
void getPosition(const OdometricLocalizer *odo, Pose *pos);

// Changes current position of an OdometricLocalizer object
void changePos(OdometricLocalizer *odo, float newX, float newY, float newH);

// Get encoder reading based on OdometricLocalizer Parameters
int getEncoderReading(OdometricLocalizer *odo, Direction side);

// Steps an OdometricLocalizer through calculations
void step_OdometricLocalizer(OdometricLocalizer *odo);

// Initializes an OdometricLocalizer with provided parameters and does init math
int init_OdometricLocalizer(OdometricLocalizer *odo, EncoderTypes type,
		int leftEncoder, int rightEncoder, float wheelDiameter,
		float trackWidth, float countsPerRevolution, bool leftFlipped,
		bool rightFlipped);

#endif //ODOMETRICLOCALIZER_H_INCLUDED

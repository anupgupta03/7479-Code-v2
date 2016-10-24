#ifndef MOTORCONTROLFUNCTIONS_H_INCLUDED
#define MOTORCONTROLFUNCTIONS_H_INCLUDED

/**
* Wait for a value to reach zero before allowing the thread to continue
*
* @param value Value to watch
*/
void waitForZero(int value);
float cJoyThreshold(int input);
int setIntakeForks(const int dir);
int toggleIntakeForks();
int setLiftLeft(const int power);
int setLiftRight(const int power);
int setDriveLeft(const int power);
int setDriveRight(const int power);
int setLift(const int power);
int driveTime(const int l_power, const int r_power, const int timeMs);
int driveStraightTime(const int power, const unsigned timeMs);
int turnTime(const int power, const int timeMs);
int turnGyro(const int power, const int deg);
int driveQuad(const int power, const int ticks);
int turnQuad(const int power, const int ticks);

#endif //MOTORCONTROLFUNCTIONS_H_INCLUDED

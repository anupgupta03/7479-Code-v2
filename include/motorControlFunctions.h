#ifndef MOTORCONTROLFUNCTIONS_H_INCLUDED
#define MOTORCONTROLFUNCTIONS_H_INCLUDED

void waitForZero(int value);
int cJoyThreshold(int i);
int setIntakeForks(const int dir);
int toggleIntakeForks();
int setLiftLeft(const int power);
int setLiftRight(const int power);
int setDriveLeft(const int power);
int setDriveRight(const int power);
int setLift(const int power);
int driveTime(const int l_power, const int r_power, const int timeMs);
int turnTime(const int power, const int timeMs);
int turnGyro(const int power, const int deg);
int driveQuad(const int power, const int ticks);
int turnQuad(const int power, const int ticks);
// int turnIME(const int power, const int ticks);
// int driveIME(const int power, const int ticks);


#endif //MOTORCONTROLFUNCTIONS_H_INCLUDED
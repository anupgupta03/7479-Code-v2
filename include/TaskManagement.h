#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

void solenoidControlTask(void *ignore);
void odoUpdateTask(void *ignore);
void joystickControlTask(void *ignore);
void watchDogManagement(void *ignore);

#endif

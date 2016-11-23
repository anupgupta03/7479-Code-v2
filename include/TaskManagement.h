/**
* @Date:   2016-10-23T16:16:26+11:00
* @Last modified time: 2016-11-23T11:34:52+11:00
*/

#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

/**
 * Main Task for solenoid control
 */
void solenoidControlTask(void *ignore);
/**
 * Main task for updating OdometricLocalizers
 */
void odoUpdateTask(void *ignore);
/**
 * Main task for joystick control
 */
void joystickControlTask(void *ignore);
/**
 * Main watchdog task for task management
 */
void watchDogManagement(void *ignore);

#endif //TASK_H_INCLUDED

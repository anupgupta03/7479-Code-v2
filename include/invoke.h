/**
* @Date:   2016-12-02T19:02:13+11:00
* @Last modified time: 2016-12-02T20:44:26+11:00
*/

#ifndef H_INVOKE_INCLUDED
#define H_INVOKE_INCLUDED

/**
 * Functions are numbered in the following format: (not that it really matters anyway)
 * First digit denotes type
 *      0 = NULL function
 *      1 = LEFT auton
 *      2 = RIGHT auton
 *      3 = Logistic function
 *      4 = Skills mode
 * Second digit denotes number in that series
 */

#define FUNC_NONE 0
#define FUNC_AUTON_LEFT_PRIMARY 11
#define FUNC_AUTON_RIGHT_PRIMARY 21
#define FUNC_RESET_SENSORS 31
#define FUNC_RESET_FUNCTIONALITY 32
#define FUNC_PROGRAMMING_SKILLS 40

/**
 * Invokes a function based on input value
 * @param func Function ID
 */
void invoke(unsigned func);

#endif // H_INVOKE_INCLUDED

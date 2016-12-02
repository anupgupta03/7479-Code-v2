/**
 * @Date:   2016-12-02T19:01:58+11:00
* @Last modified time: 2016-12-02T22:06:53+11:00
 */
#include "../include/main.h"
#include "../include/invoke.h"


void invoke(unsigned func){
	  switch (func) {
	  case FUNC_NONE:
		    return;
		    break;
	  case FUNC_AUTON_LEFT_PRIMARY:
		    globalAutonFunction = FUNC_AUTON_LEFT_PRIMARY;
		    printf("%d", globalAutonFunction);
		    break;
	  case FUNC_AUTON_RIGHT_PRIMARY:
		    globalAutonFunction = FUNC_AUTON_RIGHT_PRIMARY;
		    printf("%d", globalAutonFunction);

		    break;
	  case FUNC_PROGRAMMING_SKILLS:
		    globalAutonFunction = FUNC_PROGRAMMING_SKILLS;
		    printf("%d", globalAutonFunction);
		    break;
	  case FUNC_RESET_SENSORS:
		    resetSensors();
		    break;
	  case FUNC_RESET_FUNCTIONALITY:
		    resetFunctionality();
		    break;
	  default:
		    break;
	  }
}

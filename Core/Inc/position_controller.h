#ifndef INC_POSITION_CONTROLLER_H_
#define INC_POSITION_CONTROLLER_H_

#include "pid.h"

typedef struct {

	PID_t north;

	PID_t east;

} PositionController_t;

#endif

#ifndef INC_VELOCITY_CONTROLLER_H_
#define INC_VELOCITY_CONTROLLER_H_

#include "pid.h"

typedef struct {

	PID_t north;

	PID_t east;

} VelocityController_t;

#endif

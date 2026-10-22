/* PID vận tốc North/East, hiện chỉ khai báo kiểu. */
#ifndef INC_VELOCITY_CONTROLLER_H_
#define INC_VELOCITY_CONTROLLER_H_

#include "pid.h"

typedef struct {

	PID_t north;

	PID_t east;

} VelocityController_t;

#endif

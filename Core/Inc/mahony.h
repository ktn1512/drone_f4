#ifndef INC_MAHONY_H_
#define INC_MAHONY_H_

typedef struct {

	float q0;

	float q1;

	float q2;

	float q3;

	float twoKp;

	float twoKi;

	float integralFBx;

	float integralFBy;

	float integralFBz;

	float accel_norm_g;

	float accel_weight;

} Mahony_t;

void Mahony_Init(Mahony_t *mahony);

int Mahony_InitFromAccel(Mahony_t *mahony, float ax, float ay, float az);

void Mahony_Update(Mahony_t *mahony,

float gx, float gy, float gz,

float ax, float ay, float az,

float dt);

void Mahony_GetEuler(Mahony_t *mahony,

float *roll, float *pitch, float *yaw);

#endif

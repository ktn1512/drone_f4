/* Bộ lọc Mahony: quaternion hợp nhất gyro (độ/s) và accel (g). */
#include "mahony.h"
#include <math.h>

#define MAHONY_ACCEL_FULL_ERROR_G   0.10f // Ngưỡng 0,10g: tin accel hoàn toàn.
#define MAHONY_ACCEL_REJECT_ERROR_G 0.20f // Ngưỡng 0,20g: loại bỏ accel.
#define MAHONY_INTEGRAL_LIMIT_RAD_S 0.08726646f // Giới hạn tích phân 0,0873 rad/s = 5 độ/s.

static float clampIntegral(float value) {
	return fmaxf(-MAHONY_INTEGRAL_LIMIT_RAD_S,
	             fminf(MAHONY_INTEGRAL_LIMIT_RAD_S, value));
}

static float invSqrt(float x) {
	return 1.0f / sqrtf(x);
}

/* Khởi tạo quaternion đơn vị, twoKp=2, twoKi=0. */
void Mahony_Init(Mahony_t *m) {
	m->q0 = 1.0f;
	m->q1 = 0.0f;
	m->q2 = 0.0f;
	m->q3 = 0.0f;

	m->twoKp = 2.0f;

	m->twoKi = 0.0f;

	m->integralFBx = 0;
	m->integralFBy = 0;
	m->integralFBz = 0;
	m->accel_norm_g = 0.0f;
	m->accel_weight = 0.0f;
}

/* Khởi tạo góc Roll/Pitch từ accel, trả 1 nếu hợp lệ. */
int Mahony_InitFromAccel(Mahony_t *m, float ax, float ay, float az) {

	float normSq = ax * ax + ay * ay + az * az;
	if (!isfinite(normSq) || normSq < 1.0e-6f) {
		return 0;
	}

	float roll = atan2f(ay, az);

	float pitch = atan2f(-ax, sqrtf(ay * ay + az * az));

	float cr = cosf(0.5f * roll);

	float sr = sinf(0.5f * roll);

	float cp = cosf(0.5f * pitch);

	float sp = sinf(0.5f * pitch);

	Mahony_Init(m);

	m->q0 = cr * cp;
	m->q1 = sr * cp;
	m->q2 = cr * sp;
	m->q3 = -sr * sp;
	m->accel_norm_g = sqrtf(normSq);
	return 1;
}

void Mahony_Update(Mahony_t *m,

float gx, float gy, float gz,

float ax, float ay, float az,

float dt) {

	if (!isfinite(dt) || dt <= 0.0f ||
	    !isfinite(gx) || !isfinite(gy) || !isfinite(gz)) {
		return;
	}

	if (!(m->twoKi > 0.0f)) {
		m->integralFBx = 0.0f;
		m->integralFBy = 0.0f;
		m->integralFBz = 0.0f;
	}
	m->accel_norm_g = 0.0f;
	m->accel_weight = 0.0f;

	float recipNorm;

	float halfvx;

	float halfvy;

	float halfvz;

	float halfex;

	float halfey;

	float halfez;

	float qa;

	float qb;

	float qc;

	gx *= 0.0174533f;
	gy *= 0.0174533f;
	gz *= 0.0174533f;

	float accelNormSq = ax * ax + ay * ay + az * az;
	if (isfinite(accelNormSq) && accelNormSq >= 1.0e-6f) {
		m->accel_norm_g = sqrtf(accelNormSq);
		float normError = fabsf(m->accel_norm_g - 1.0f);
		if (normError <= MAHONY_ACCEL_FULL_ERROR_G) {
			m->accel_weight = 1.0f;
		} else if (normError < MAHONY_ACCEL_REJECT_ERROR_G) {
			m->accel_weight = (MAHONY_ACCEL_REJECT_ERROR_G - normError) /
			                  (MAHONY_ACCEL_REJECT_ERROR_G - MAHONY_ACCEL_FULL_ERROR_G);
		}
	}
	if (m->accel_weight > 0.0f) {
		recipNorm = 1.0f / m->accel_norm_g;

		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		halfvx = m->q1 * m->q3 - m->q0 * m->q2;

		halfvy = m->q0 * m->q1 + m->q2 * m->q3;

		halfvz = m->q0 * m->q0 - 0.5f + m->q3 * m->q3;

		halfex = ay * halfvz - az * halfvy;
		halfey = az * halfvx - ax * halfvz;
		halfez = ax * halfvy - ay * halfvx;

		halfex *= m->accel_weight;
		halfey *= m->accel_weight;
		halfez *= m->accel_weight;
		if (m->twoKi > 0.0f) {
			m->integralFBx = clampIntegral(m->integralFBx + m->twoKi * halfex * dt);
			m->integralFBy = clampIntegral(m->integralFBy + m->twoKi * halfey * dt);
			m->integralFBz = clampIntegral(m->integralFBz + m->twoKi * halfez * dt);
		}

		gx += m->twoKp * halfex;
		gy += m->twoKp * halfey;
		gz += m->twoKp * halfez;
	}

	gx += m->integralFBx;
	gy += m->integralFBy;
	gz += m->integralFBz;

	gx *= 0.5f * dt;
	gy *= 0.5f * dt;
	gz *= 0.5f * dt;

	qa = m->q0;
	qb = m->q1;
	qc = m->q2;

	m->q0 += (-qb * gx - qc * gy - m->q3 * gz);
	m->q1 += (qa * gx + qc * gz - m->q3 * gy);
	m->q2 += (qa * gy - qb * gz + m->q3 * gx);
	m->q3 += (qa * gz + qb * gy - qc * gx);

	recipNorm = invSqrt(
			m->q0 * m->q0 + m->q1 * m->q1 + m->q2 * m->q2 + m->q3 * m->q3);

	m->q0 *= recipNorm;
	m->q1 *= recipNorm;
	m->q2 *= recipNorm;
	m->q3 *= recipNorm;
}

void Mahony_GetEuler(Mahony_t *m,

float *roll, float *pitch, float *yaw) {
	*roll = atan2f(2.0f * (m->q0 * m->q1 + m->q2 * m->q3),
			1.0f - 2.0f * (m->q1 * m->q1 + m->q2 * m->q2)) * 57.29578f;

	float sinPitch = 2.0f * (m->q0 * m->q2 - m->q3 * m->q1);
	sinPitch = fmaxf(-1.0f, fminf(1.0f, sinPitch));
	*pitch = asinf(sinPitch) * 57.29578f;

	*yaw = atan2f(2.0f * (m->q0 * m->q3 + m->q1 * m->q2),
			1.0f - 2.0f * (m->q2 * m->q2 + m->q3 * m->q3)) * 57.29578f;
}

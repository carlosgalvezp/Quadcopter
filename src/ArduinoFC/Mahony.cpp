#include "Mahony.h"

namespace Mahony
{
	volatile float twoKp = twoKpDef;											// 2 * proportional gain (Kp)
	volatile float twoKi = twoKiDef;											// 2 * integral gain (Ki)
	volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;					// quaternion of sensor frame relative to auxiliary frame
	volatile float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f;	// integral error terms scaled by Ki

	volatile unsigned long last_t=0;
	volatile float deltaT;

	void MARGupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
	{
		float recipNorm;
		float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
		float hx, hy, bx, bz;
		float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
		float halfex, halfey, halfez;
		float qa, qb, qc;

		if (last_t == 0)
		{
			last_t = micros();
			return;
		}
		else
		{
			deltaT = 0.000001f * (micros() - last_t);
			last_t = micros();
		}

		//// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
		//if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
		//	MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		//	return;
		//}

		// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
		if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

			// Normalise accelerometer measurement
			recipNorm = Utils::invSqrt(ax * ax + ay * ay + az * az);
			ax *= recipNorm;
			ay *= recipNorm;
			az *= recipNorm;

			// Normalise magnetometer measurement
			recipNorm = Utils::invSqrt(mx * mx + my * my + mz * mz);
			mx *= recipNorm;
			my *= recipNorm;
			mz *= recipNorm;

			// Auxiliary variables to avoid repeated arithmetic
			q0q0 = q0 * q0;
			q0q1 = q0 * q1;
			q0q2 = q0 * q2;
			q0q3 = q0 * q3;
			q1q1 = q1 * q1;
			q1q2 = q1 * q2;
			q1q3 = q1 * q3;
			q2q2 = q2 * q2;
			q2q3 = q2 * q3;
			q3q3 = q3 * q3;

			// Reference direction of Earth's magnetic field
			hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
			hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
			bx = sqrt(hx * hx + hy * hy);
			bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

			// Estimated direction of gravity and magnetic field
			halfvx = q1q3 - q0q2;
			halfvy = q0q1 + q2q3;
			halfvz = q0q0 - 0.5f + q3q3;
			halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
			halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
			halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

			// Error is sum of cross product between estimated direction and measured direction of field vectors
			halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
			halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
			halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

			// Compute and apply integral feedback if enabled
			if (twoKi > 0.0f) {
				integralFBx += twoKi * halfex * deltaT;	// integral error scaled by Ki
				integralFBy += twoKi * halfey * deltaT;
				integralFBz += twoKi * halfez * deltaT;
				gx += integralFBx;	// apply integral feedback
				gy += integralFBy;
				gz += integralFBz;
			}
			else {
				integralFBx = 0.0f;	// prevent integral windup
				integralFBy = 0.0f;
				integralFBz = 0.0f;
			}

			// Apply proportional feedback
			gx += twoKp * halfex;
			gy += twoKp * halfey;
			gz += twoKp * halfez;
		}

		// Integrate rate of change of quaternion
		gx *= (0.5f * deltaT);		// pre-multiply common factors
		gy *= (0.5f * deltaT);
		gz *= (0.5f * deltaT);
		qa = q0;
		qb = q1;
		qc = q2;
		q0 += (-qb * gx - qc * gy - q3 * gz);
		q1 += (qa * gx + qc * gz - q3 * gy);
		q2 += (qa * gy - qb * gz + q3 * gx);
		q3 += (qa * gz + qb * gy - qc * gx);

		// Normalise quaternion
		recipNorm = Utils::invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
		q0 *= recipNorm;
		q1 *= recipNorm;
		q2 *= recipNorm;
		q3 *= recipNorm;
	}

	
	void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az) {
		float recipNorm;
		float halfvx, halfvy, halfvz;
		float halfex, halfey, halfez;
		float qa, qb, qc;

		// Compute deltaT
		if (last_t == 0)
		{
			last_t = micros();
			return;
		}
		else
		{
			deltaT = 0.000001f * (micros() - last_t);
			last_t = micros();
		}

		// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
		if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

			// Normalise accelerometer measurement
			recipNorm = Utils::invSqrt(ax * ax + ay * ay + az * az);
			ax *= recipNorm;
			ay *= recipNorm;
			az *= recipNorm;

			// Estimated direction of gravity and vector perpendicular to magnetic flux
			halfvx = q1 * q3 - q0 * q2;
			halfvy = q0 * q1 + q2 * q3;
			halfvz = q0 * q0 - 0.5f + q3 * q3;

			// Error is sum of cross product between estimated and measured direction of gravity
			halfex = (ay * halfvz - az * halfvy);
			halfey = (az * halfvx - ax * halfvz);
			halfez = (ax * halfvy - ay * halfvx);

			// Compute and apply integral feedback if enabled
			if (twoKi > 0.0f) {
				integralFBx += twoKi * halfex * deltaT;	// integral error scaled by Ki
				integralFBy += twoKi * halfey * deltaT;
				integralFBz += twoKi * halfez * deltaT;
				gx += integralFBx;	// apply integral feedback
				gy += integralFBy;
				gz += integralFBz;
			}
			else {
				integralFBx = 0.0f;	// prevent integral windup
				integralFBy = 0.0f;
				integralFBz = 0.0f;
			}

			// Apply proportional feedback
			gx += twoKp * halfex;
			gy += twoKp * halfey;
			gz += twoKp * halfez;
		}

		// Integrate rate of change of quaternion
		gx *= (0.5f * deltaT);		// pre-multiply common factors
		gy *= (0.5f * deltaT);
		gz *= (0.5f * deltaT);
		qa = q0;
		qb = q1;
		qc = q2;
		q0 += (-qb * gx - qc * gy - q3 * gz);
		q1 += (qa * gx + qc * gz - q3 * gy);
		q2 += (qa * gy - qb * gz + q3 * gx);
		q3 += (qa * gz + qb * gy - qc * gx);

		// Normalise quaternion
		recipNorm = Utils::invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
		q0 *= recipNorm;
		q1 *= recipNorm;
		q2 *= recipNorm;
		q3 *= recipNorm;
	}

	void getQuaternion(quaternion_t * const q)
	{
		q->q0 = q0;
		q->q1 = q1;
		q->q2 = q2;
		q->q3 = q3;
	}

}
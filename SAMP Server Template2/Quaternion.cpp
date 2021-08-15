#include "Vector3.h"
#include "Quaternion.h"
#include <cmath>

SAMP::Quaternion::Quaternion()
{
	x = y = z = w = 0.0f;
}

SAMP::Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
}

Vector3 SAMP::Quaternion::ToEulerAngles()
{
	//Be sure to switch the axes if necessary.
	//Code was yoinked online. Might not work as intended
	Vector3 angles = Vector3();
	// roll (x-axis rotation)
	double sinr_cosp = 2 * (this->w * this->x + this->y * this->z);
	double cosr_cosp = 1 - 2 * (this->x * this->x + this->y * this->y);
	angles.x = (float)atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (this->w * this->y - this->z * this->x);
	if (abs(sinp) >= 1)
		angles.y = (float)copysign(3.14 / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = (float)asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (this->w * this->z + this->x * this->y);
	double cosy_cosp = 1 - 2 * (this->y * this->y + this->z * this->z);
	angles.z = (float)atan2(siny_cosp, cosy_cosp);

	return angles;
}

void SAMP::Quaternion::FromEulerAngles(Vector3 angles)
{
	//Be sure to switch the axes if necessary.
	//Code was yoinked online. Might not work as intended
	double cy = cos(angles.z * 0.5);//YAW
	double sy = sin(angles.z * 0.5);
	double cp = cos(angles.y * 0.5);//PITCH
	double sp = sin(angles.y * 0.5);
	double cr = cos(angles.x * 0.5);//ROLL
	double sr = sin(angles.x * 0.5);

	Quaternion q;
	this->w = (float)(cr * cp * cy + sr * sp * sy);
	this->x = (float)(sr * cp * cy - cr * sp * sy);
	this->y = (float)(cr * sp * cy + sr * cp * sy);
	this->z = (float)(cr * cp * sy - sr * sp * cy);

	return;
}

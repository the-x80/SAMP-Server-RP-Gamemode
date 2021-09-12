#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	x = y = z = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::Normalized()
{
	return Vector3();
}

float Vector3::MagnitudeSquared()
{
	return 0.0f;
}

float Vector3::Magnitude()
{
	return 0.0f;
}

float Vector3::Dot(Vector3 v1, Vector3 v2)
{
	return 0.0f;
}

float Vector3::Distance(Vector3 v1, Vector3 v2)
{
	float v1powx = (v2.x*v2.x);
	return (float)sqrt( pow((double)v2.x-v1.x, 2) + pow((double)v2.y - v1.y, 2) + pow((double)v2.z - v1.z, 2));
}

Vector3& Vector3::operator+(Vector3 other)
{
	return Vector3(this->x+other.x, this->y+other.y, this->z + other.z);
}

Vector3& Vector3::operator-(Vector3 other)
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3& Vector3::operator*(float other)
{
	return Vector3(this->x * other, this->y * other, this->z * other);
}

Vector3& Vector3::operator/(float other)
{
	return Vector3(this->x / other, this->y / other, this->z / other);
}

bool Vector3::operator==(Vector3 other)
{
	
	return false;
}

bool Vector3::operator!=(Vector3 other)
{
	
	return false;
}


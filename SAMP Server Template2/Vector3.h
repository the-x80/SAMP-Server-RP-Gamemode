#ifndef VECTOR3_H
#define VECTOR3_H
class Vector3
{
public:
	float x, y, z;


	Vector3();
	Vector3(float _x, float _y, float _z);

	Vector3 Normalized();
	float MagnitudeSquared();
	float Magnitude();

	static float Dot(Vector3 v1, Vector3 v2);
	float Distance(Vector3 v1, Vector3 v2);
	//The dot product of two vectors
	
	

	Vector3& operator +(Vector3 other);
	Vector3& operator -(Vector3 other);
	Vector3& operator *(float other);
	Vector3& operator /(float other);
	bool operator ==(Vector3 other);
	bool operator !=(Vector3 other);
	
};

#endif
#ifndef QUATERNION_H
#define QUATERNION_H


namespace SAMP {
	
	class Quaternion
	{
	public:
		float x, y, z, w;
		Quaternion();
		Quaternion(float _w, float _x, float _y, float _z);

		Vector3 ToEulerAngles();
		void FromEulerAngles(Vector3 angles);

		//Implement operators
	};
}
#endif

#pragma once
#include "Vec2.h"
#include "Vec3d.h"
class Vec3 : public Vec2{
	
public:
	float z;

	Vec3(void);
	Vec3(Vec3d vector);
	Vec3(float x, float y, float z);
	void normalize();
	float length();
	static float dot(Vec3 left, Vec3 right);
	// Operatoren
	void operator+=(float skalar);
	void operator+=(Vec3 vector);
	void operator-=(float skalar);
	void operator-=(Vec3 vector);
	Vec3 operator*(float skalar);
	Vec3 operator*(Vec3 vector);
	Vec3 operator-();
	Vec3 operator-(Vec3 vector);
	Vec3 operator+(Vec3 vector);
	bool operator!=(Vec3 vector);

	bool isAxisOriented();
	~Vec3(void);
};


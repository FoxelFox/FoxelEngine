#pragma once
#include "Vec2.h"
class Vec3 : public Vec2{
	
public:
	float z;

	Vec3(void);
	Vec3(float x, float y, float z);
	// Operatoren
	void operator+=(float skalar);
	void operator+=(Vec3 vector);
	void operator-=(float skalar);
	void operator-=(Vec3 vector);
	Vec3 operator*(float skalar);
	Vec3 operator*(Vec3 vector);
	Vec3 operator-();
	~Vec3(void);
};


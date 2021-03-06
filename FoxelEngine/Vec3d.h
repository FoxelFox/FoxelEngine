#pragma once
#include "Vec2d.h"
class Vec3d : public Vec2d{
	
public:
	double z;

	Vec3d(void);
	Vec3d(double x, double y, double z);
	void normalize();
	double length();
	static double dot(Vec3d left, Vec3d right);
	// Operatoren
	void operator+=(double skalar);
	void operator+=(Vec3d vector);
	void operator-=(double skalar);
	void operator-=(Vec3d vector);
	Vec3d operator*(double skalar);
	Vec3d operator*(Vec3d vector);
	Vec3d operator-();
	Vec3d operator-(Vec3d vector);
	Vec3d operator+(Vec3d vector);
	bool operator!=(Vec3d vector);
	~Vec3d(void);
};


#include "Vec3d.h"

Vec3d::Vec3d(void) : Vec2d(){
	z = 0;
}

Vec3d::Vec3d(double x,double y,double z) : Vec2d(x,y){
	Vec3d::z = z;
}

void Vec3d::operator+=(double skalar){
	Vec3d::x += skalar;
	Vec3d::y += skalar;
	Vec3d::z += skalar;
}

void Vec3d::operator+=(Vec3d vector){
	Vec3d::x += vector.x;
	Vec3d::y += vector.y;
	Vec3d::z += vector.z;
}

void Vec3d::operator-=(double skalar){
	Vec3d::x -= skalar;
	Vec3d::y -= skalar;
	Vec3d::z -= skalar;
}

void Vec3d::operator-=(Vec3d vector){
	Vec3d::x -= vector.x;
	Vec3d::y -= vector.y;
	Vec3d::z -= vector.z;
}

Vec3d Vec3d::operator*(double skalar){
	Vec3d tmp = *this;
	tmp.x *= skalar;
	tmp.y *= skalar;
	tmp.z *= skalar;
	return tmp;
}

Vec3d Vec3d::operator*(Vec3d vector){
	Vec3d tmp = *this;
	tmp.x *= vector.x;
	tmp.y *= vector.y;
	tmp.z *= vector.z;
	return tmp;
}

Vec3d Vec3d::operator-(){
	Vec3d tmp = *this;
	tmp.x *= -1;
	tmp.y *= -1;
	tmp.z *= -1;
	return tmp;
}

Vec3d::~Vec3d(void)
{
}

#include "Vec3d.h"
#include <math.h>

Vec3d::Vec3d(void) : Vec2d(){
	z = 0;
}

Vec3d::Vec3d(double x,double y,double z) : Vec2d(x,y){
	Vec3d::z = z;
}

double Vec3d::length(){
	return (float) sqrt((x * x) + (y * y) + (z * z));
}

void Vec3d::normalize(){
	 double num = 1.0f / length();
	 x *= num;
	 y *= num;
	 z *= num;
}

double Vec3d::dot(Vec3d left, Vec3d right)
{
	return (((left.x * right.x) + (left.y * right.y)) + (left.z * right.z));
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

Vec3d Vec3d::operator-(Vec3d vector){
	Vec3d tmp = *this;
	tmp.x -= vector.x;
	tmp.y -= vector.y;
	tmp.z -= vector.z;
	return tmp;
}

Vec3d Vec3d::operator+(Vec3d vector){
	Vec3d tmp = *this;
	tmp.x += vector.x;
	tmp.y += vector.y;
	tmp.z += vector.z;
	return tmp;
}

bool Vec3d::operator!=(Vec3d vector){
	const float t = 0.5f;
	if(x > vector.x - t && x < vector.x + t
	&& y > vector.y - t && y < vector.y + t
	&& z > vector.z - t && z < vector.z + t){
		return false;
	}
	return true;
}

Vec3d::~Vec3d(void)
{
}

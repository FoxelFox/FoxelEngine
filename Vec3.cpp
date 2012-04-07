#include "Vec3.h"

Vec3::Vec3(void) : Vec2(){
	z = 0;
}

Vec3::Vec3(float x,float y,float z) : Vec2(x,y){
	Vec3::z = z;
}

void Vec3::operator+=(float skalar){
	Vec3::x += skalar;
	Vec3::y += skalar;
	Vec3::z += skalar;
}

void Vec3::operator+=(Vec3 vector){
	Vec3::x += vector.x;
	Vec3::y += vector.y;
	Vec3::z += vector.z;
}

void Vec3::operator-=(float skalar){
	Vec3::x -= skalar;
	Vec3::y -= skalar;
	Vec3::z -= skalar;
}

void Vec3::operator-=(Vec3 vector){
	Vec3::x -= vector.x;
	Vec3::y -= vector.y;
	Vec3::z -= vector.z;
}

Vec3 Vec3::operator*(float skalar){
	Vec3 tmp = *this;
	tmp.x *= skalar;
	tmp.y *= skalar;
	tmp.z *= skalar;
	return tmp;
}

Vec3 Vec3::operator*(Vec3 vector){
	Vec3 tmp = *this;
	tmp.x *= vector.x;
	tmp.y *= vector.y;
	tmp.z *= vector.z;
	return tmp;
}

Vec3 Vec3::operator-(){
	Vec3 tmp = *this;
	tmp.x *= -1;
	tmp.y *= -1;
	tmp.z *= -1;
	return tmp;
}

Vec3::~Vec3(void)
{
}

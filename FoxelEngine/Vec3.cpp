#include "Vec3.h"
#include <math.h>

Vec3::Vec3(void) : Vec2(){
	z = 0;
}

Vec3::Vec3(Vec3d vector){
	x = (float)vector.x;
	y = (float)vector.y;
	z = (float)vector.z;
}

Vec3::Vec3(float x,float y,float z) : Vec2(x,y){
	Vec3::z = z;
}

float Vec3::length(){
	return (float) sqrt((x * x) + (y * y) + (z * z));
}

void Vec3::normalize(){
	 float num = 1.0f / length();
	 x *= num;
	 y *= num;
	 z *= num;
}

float Vec3::dot(Vec3 left, Vec3 right)
{
	return (((left.x * right.x) + (left.y * right.y)) + (left.z * right.z));
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

Vec3 Vec3::operator-(Vec3 vector){
	Vec3 tmp = *this;
	tmp.x -= vector.x;
	tmp.y -= vector.y;
	tmp.z -= vector.z;
	return tmp;
}

Vec3 Vec3::operator+(Vec3 vector){
	Vec3 tmp = *this;
	tmp.x += vector.x;
	tmp.y += vector.y;
	tmp.z += vector.z;
	return tmp;
}

bool Vec3::operator!=(Vec3 vector){
	const float t = 0.5f;
	if(x > vector.x - t && x < vector.x + t
	&& y > vector.y - t && y < vector.y + t
	&& z > vector.z - t && z < vector.z + t){
		return false;
	}
	return true;
}

/*
	Just use it for normalized vectors!
*/
bool Vec3::isAxisOriented(){
	if(x == 1 || x == -1 || y == 1 || y == -1 || z == 1 || z == -1) return true;
	else return false;
}

Vec3::~Vec3(void)
{
}

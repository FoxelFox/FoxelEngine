#include "Vec2.h"
#include <math.h>

const double PI = 3.141592653589;

Vec2::Vec2(void){
	x = 0;
	y = 0;
}

Vec2::Vec2(float x,float y){
	Vec2::x = x;
	Vec2::y = y;
}

void Vec2::operator+=(float skalar){
	Vec2::x += skalar;
	Vec2::y += skalar;
}

void Vec2::operator+=(Vec2 vector){
	Vec2::x += vector.x;
	Vec2::y += vector.y;
}

void Vec2::operator-=(float skalar){
	Vec2::x -= skalar;
	Vec2::y -= skalar;
}

void Vec2::operator-=(Vec2 vector){
	Vec2::x -= vector.x;
	Vec2::y -= vector.y;
}

Vec2 Vec2::operator*(float skalar){
	Vec2 tmp = *this;
	tmp.x *= skalar;
	tmp.y *= skalar;
	return tmp;
}

Vec2 Vec2::operator*(Vec2 vector){
	Vec2 tmp = *this;
	tmp.x *= vector.x;
	tmp.y *= vector.y;
	return tmp;
}

Vec2 Vec2::operator+(float skalar){
	Vec2 tmp = *this;
	tmp.x += skalar;
	tmp.y += skalar;
	return tmp;
}

Vec2 Vec2::operator+(Vec2 vector){
	Vec2 tmp = *this;
	tmp.x += vector.x;
	tmp.y += vector.y;
	return tmp;
}

Vec2 Vec2::operator-(float skalar){
	Vec2 tmp = *this;
	tmp.x -= skalar;
	tmp.y -= skalar;
	return tmp;
}

Vec2 Vec2::operator-(Vec2 vector){
	Vec2 tmp = *this;
	tmp.x -= vector.x;
	tmp.y -= vector.y;
	return tmp;
}

Vec2 Vec2::operator-(){
	Vec2 tmp = *this;
	tmp.x *= -1;
	tmp.y *= -1;
	return tmp;
}

float Vec2::length(){
	return (float) sqrt((x * x) + (y * y));
}

void Vec2::normalize(){
	 float num = 1.0f / length();
	 x *= num;
	 y *= num;
}

float Vec2::dot(Vec2 left, Vec2 right)
{
	return (((left.x * right.x) + (left.y * right.y)));
}

void Vec2::rotate(Vec2 center, double phi){
	double xx,yy,xxx,yyy;
		
	phi *= (PI / 180); // degToRad
		
	xx = x - center.x;
	yy = y - center.y;
		
	xxx =  xx * cos(phi) + yy * sin(phi);
	yyy = -xx * sin(phi) + yy * cos(phi);
		
	Vec2::x = xxx + center.x;
	Vec2::y = yyy + center.y;
}

Vec2::~Vec2(void)
{
}

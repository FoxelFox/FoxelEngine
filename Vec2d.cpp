#include "Vec2d.h"

Vec2d::Vec2d(void){
	x = 0;
	y = 0;
}

Vec2d::Vec2d(double x,double y){
	Vec2d::x = x;
	Vec2d::y = y;
}

void Vec2d::operator+=(double skalar){
	Vec2d::x += skalar;
	Vec2d::y += skalar;
}

void Vec2d::operator+=(Vec2d vector){
	Vec2d::x += vector.x;
	Vec2d::y += vector.y;
}

void Vec2d::operator-=(double skalar){
	Vec2d::x -= skalar;
	Vec2d::y -= skalar;
}

void Vec2d::operator-=(Vec2d vector){
	Vec2d::x -= vector.x;
	Vec2d::y -= vector.y;
}

Vec2d Vec2d::operator*(double skalar){
	Vec2d tmp = *this;
	tmp.x *= skalar;
	tmp.y *= skalar;
	return tmp;
}

Vec2d Vec2d::operator*(Vec2d vector){
	Vec2d tmp = *this;
	tmp.x *= vector.x;
	tmp.y *= vector.y;
	return tmp;
}

Vec2d Vec2d::operator-(){
	Vec2d tmp = *this;
	tmp.x *= -1;
	tmp.y *= -1;
	return tmp;
}

Vec2d::~Vec2d(void)
{
}

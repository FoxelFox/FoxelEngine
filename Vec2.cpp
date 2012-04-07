#include "Vec2.h"

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

Vec2 Vec2::operator-(){
	Vec2 tmp = *this;
	tmp.x *= -1;
	tmp.y *= -1;
	return tmp;
}

Vec2::~Vec2(void)
{
}

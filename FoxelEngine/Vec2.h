#pragma once
class Vec2{
	
public:
	float x,y;

	Vec2(void);
	Vec2(float x, float y);
	// Operatoren
	void operator+=(float skalar);
	void operator+=(Vec2 vector);
	void operator-=(float skalar);
	void operator-=(Vec2 vector);
	Vec2 operator*(float skalar);
	Vec2 operator*(Vec2 vector);
	Vec2 operator-();
	~Vec2(void);
};
#pragma once
class Vec2d{
	
public:
	double x,y;

	Vec2d(void);
	Vec2d(double x, double y);
	// Operatoren
	void operator+=(double skalar);
	void operator+=(Vec2d vector);
	void operator-=(double skalar);
	void operator-=(Vec2d vector);
	Vec2d operator*(double skalar);
	Vec2d operator*(Vec2d vector);
	Vec2d operator-();
	~Vec2d(void);
};
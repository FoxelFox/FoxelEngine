#pragma once
#include "Vec2.h"
#include "Color.h"
class Entity_2D{
protected:
	Vec2 size;
	Vec2 position;
	Color backColor;
public:
	Entity_2D(Vec2 position, Vec2 size);
	Entity_2D(void);
	~Entity_2D(void);
	Vec2 getPosition();
	Vec2 getSize();
	void setBackColor(Color color);
	void setPosition(Vec2 position);
	void setSize(Vec2 size);
	void move(Vec2 value);
	void drawBackground();
	bool mouseIntersect();
};


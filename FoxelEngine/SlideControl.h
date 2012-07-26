#pragma once
#include <sstream>
#include "Entity_2D.h"
#include "TextField.h"
class SlideControl : public Entity_2D{
private:
	double value;
	double buffValue;
	TextField* text;
	void setText();
	std::string prefix;
public:
	SlideControl(Vec2 position, Vec2 size, std::string prefix);

	void changeValue(float value);
	void setValue(float value);
	void draw();
	void setPosition(Vec2 position);
	float getValue();
};


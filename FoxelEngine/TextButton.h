#pragma once
#include "TextField.h"



class TextButton : public TextField{
	bool pressed;
public:
	TextButton(Vec2 position, Vec2 size, std::string content);
	void press();
	void release();
	bool isPressed();
	bool intersect(Vec2 point);
	~TextButton(void);
};


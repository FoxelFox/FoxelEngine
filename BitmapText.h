#pragma once
#include <string>
#include <sstream>
#include <GL\freeglut.h>
#include <stdio.h>
#include "Vec3.h"

class BitmapText{

private:
	std::string text;

public:
	BitmapText(std::string);
	~BitmapText(void);
	
	void setText(std::string);
	void draw();
};


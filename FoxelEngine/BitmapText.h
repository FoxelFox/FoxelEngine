#pragma once
#include <string>
#include <sstream>
#include <stdio.h>
#include "Vec3.h"
#include "Screen.h"

class BitmapText{

private:
	std::string text;
	bool bigText;
public:
	BitmapText(std::string);
	~BitmapText(void);
	
	void setBigText(bool boolean);
	void setText(std::string);
	void draw();
};


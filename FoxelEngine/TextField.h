#pragma once
#include <string>
#include <vector>
#include "Entity_2D.h"
#include "BitMapText.h"
//#include <GL/gl.h>


class TextField : public Entity_2D{

protected:
	std::vector<BitmapText> linesOfContent;
	int* displayWidth;
	int* displayHeight;
	bool withBox;
	int boxPadding;
	GLfloat textColor[3];

public:
	TextField(Vec2 position, Vec2 size, std::string);
	TextField(Vec2 position, Vec2 size);
	~TextField(void);

	Vec2 getPosition();
	void setContent(int,std::string);
	void setTextColor(float r, float g, float b);
	void draw();
	void newLine(std::string);
};
#pragma once

#include <GL\glew.h>

class Foxel {

private:
	GLushort color[3];
	char id;
	char visiblity;
	bool test;

public:
	Foxel();
	Foxel(char idFoxel, char vis);
	~Foxel();
	void setColor(GLushort r, GLushort g, GLushort b);
	void setVisiblity(char setBit);
	char getVisiblity();
	void setId(char);
	char getId();
	GLushort* getColor();
};

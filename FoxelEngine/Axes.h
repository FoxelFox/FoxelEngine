#pragma once
#include <GL\glew.h>
#include "drawablegamecomponent.h"

const GLfloat lineVertices[] = {0,0,0,
								8,0,0,
								0,8,0,
								0,0,8};

const GLfloat color[]		=  {0,0,0,
							    1,0,0,
							    0,1,0,
							    0,0,1};

const GLushort indices[] = {0,1,0,2,0,3};

class Axes :
	public DrawableGameComponent
{
private:

public:
	Axes(void);
	void render();
	~Axes(void);
};


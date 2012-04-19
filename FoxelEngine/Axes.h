#pragma once
#include <GL\glew.h>
#include "drawablegamecomponent.h"

static GLfloat AxeVertices[] = {0,0,0,
                                8,0,0,
                                0,8,0,
                                0,0,8};

static GLfloat AxeColor[] = {0,0,0,
                             1,0,0,
                             0,1,0,
                             0,0,1};

static GLuint AxeIndices[] = {0,1,0,2,0,3};

class Axes : public DrawableGameComponent{
private:
	//VertexPositionColor* vertices;
public:
	Axes(void);
	~Axes(void);
	void render();
};


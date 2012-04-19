#pragma once
#include <GL\glew.h>
#include "gamecomponent.h"

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i)) // for VBO

class DrawableGameComponent :
	public GameComponent
{
protected:
	GLfloat *vertices, *colors, *normals;
	GLuint vao, *indices, vbos[3];
	unsigned int anzVertex;
	unsigned int anzIndex;
	unsigned int anzPolygon;
public:
	DrawableGameComponent(void);
	~DrawableGameComponent(void);
	void load();
};


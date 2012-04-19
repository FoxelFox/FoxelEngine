#include "DrawableGameComponent.h"
#include <iostream>

DrawableGameComponent::DrawableGameComponent(void){
}

DrawableGameComponent::~DrawableGameComponent(void)
{
}

void DrawableGameComponent::load(){
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glGenBuffers(3,vbos);

	// vertex data
	glBindBuffer(GL_ARRAY_BUFFER,vbos[0]);
	glBufferData(GL_ARRAY_BUFFER,anzVertex*sizeof(GLfloat)*3,vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,0,0);

	// Color data
	glBindBuffer(GL_ARRAY_BUFFER,vbos[1]);
	glBufferData(GL_ARRAY_BUFFER,anzVertex*sizeof(GLfloat)*3,colors,GL_STATIC_DRAW);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE,0,0);

	// index data
	glBindBuffer(GL_ARRAY_BUFFER,vbos[2]);
	glBufferData(GL_ARRAY_BUFFER,anzIndex*sizeof(GL_UNSIGNED_INT),indices,GL_STATIC_DRAW);


	glBindVertexArray(0);
}
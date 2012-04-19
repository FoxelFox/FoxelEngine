#include "Axes.h"


Axes::Axes(void){
	anzVertex = 4;
	anzIndex = 6;
	indices = AxeIndices;
	vertices = AxeVertices;
	colors = AxeColor;
}

void Axes::render(){
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_LINES,6,GL_UNSIGNED_INT,indices);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

Axes::~Axes(void){
}

#include "Axes.h"


Axes::Axes(void){
}

void Axes::render(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,lineVertices);
	glColorPointer(3,GL_FLOAT,0,color);
	glDrawElements(GL_LINES,6,GL_UNSIGNED_SHORT,indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

Axes::~Axes(void){
}

#include "View.h"
#include <GL\freeglut.h>

using namespace MapEditor;

View::View(char viewMode, Vec2 position, Vec2 size) : Entity_2D(position, size){
	this->viewMode = viewMode;
}

View::~View(void){
}

void View::setUp(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport((GLsizei)position.x, (GLsizei)position.y, (GLsizei)size.x, (GLsizei)size.y);
	//glLoadIdentity();

	glOrtho(-size.x/2,size.x/2,-size.y/2,size.y/2,-128,128);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	const float xMin = -size.x/2+1;
	const float xMax =  size.x/2;
	const float yMin = -size.y/2+1;
	const float yMax =  size.y/2;
	// draw Background
	glBegin(GL_QUADS);
	glColor3f(0.12f,0.12f,0.12f);	glVertex3f(xMin,yMin, -128);
									glVertex3f(xMax,yMin, -128);																
	glColor3f(0.30f,0.30f,0.30f);	glVertex3f(xMax,yMax, -128);
									glVertex3f(xMin,yMax, -128);
	glEnd();

	// draw boxline
	glColor3f(0.5f,0.5f,0.5f);
	glBegin(GL_LINE_LOOP);
		glVertex3f(xMin,yMin, -127.5);
		glVertex3f(xMin,yMax, -127.5);
		glVertex3f(xMax,yMax, -127.5);
		glVertex3f(xMax,yMin, -127.5);
	glEnd();

	glScalef(32,32,32);
	switch(viewMode){
		glPushMatrix();
		case VIEW_TOP:
		{
			glRotatef(0,0,0,0);
			break;
		}
		case VIEW_FRONT:
		{
			glRotatef(-90,1,0,0);
			break;
		}
		case VIEW_RIGHT:
		{
			glRotatef(-90,1,0,0);
			glRotatef(90,0,0,1);
			break;
		}
	}
		
	if(viewMode == VIEW_3D){
		float ar = (float) size.x / (float) size.y;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-ar, ar, -1.0, 1.0, 2.0, 16000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glRotatef(-90,1,0,0);
		glTranslatef(0,8,0);
	}
}

void View::draw(){
	axes.render();
	glutSolidTeapot(1);
}

void View::setSize(Vec2 size){
	this->size = size;
}

Vec2 View::getSize(){
	return size;
}
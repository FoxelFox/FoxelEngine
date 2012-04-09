#include "View.h"
#include <GL\freeglut.h>
#include <math.h>
#include <iostream>

using namespace MapEditor;

int lines = 0; // debug

View::View(char viewMode, Vec2 position, Vec2 size) : Entity_2D(position, size){
	this->viewMode = viewMode;
	if(viewMode == VIEW_3D) ePlayer = new Player(PLAYER_EDIT);
	zoom = 4;
	gridDeep = 8;
}

View::~View(void){
}

void View::setUp(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport((GLsizei)position.x, (GLsizei)position.y, (GLsizei)size.x, (GLsizei)size.y);
	//glLoadIdentity();

	glOrtho(-size.x/2, size.x/2, -size.y/2, size.y/2,-128,128);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	const float xMin = -size.x/2+1;
	const float xMax =  size.x/2;
	const float yMin = -size.y/2+1;
	const float yMax =  size.y/2;
	// draw Background
	glBegin(GL_QUADS);
	glColor3f(0.02f,0.02f,0.02f);	glVertex3f(xMin,yMin, -128);
									glVertex3f(xMax,yMin, -128);																
	glColor3f(0.15f,0.15f,0.15f);	glVertex3f(xMax,yMax, -128);
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

	glScalef(zoom,zoom,zoom);
	if(viewMode > 0) drawGrid();

	

	switch(viewMode){
		case VIEW_TOP:
		{
			glRotatef(0,0,0,0);
			glTranslatef(-viewPosition.x,-viewPosition.y,0);
			break;
		}
		case VIEW_FRONT:
		{
			glRotatef(-90,1,0,0);
			glTranslatef(-viewPosition.x,0,-viewPosition.y);
			break;
		}
		case VIEW_RIGHT:
		{
			glRotatef(-90,1,0,0);
			glRotatef(90,0,0,1);
			glTranslatef(0, viewPosition.x, -viewPosition.y);
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
		ePlayer->render();
	}
}

void View::update(float* time){
	if(viewMode == VIEW_3D) ePlayer->update(time);
}

void View::draw(){
	glColor3f(0.5,0.5,0.5);
	axes.render();
	glutSolidTeapot(1);
}

void View::drawGrid(){
	glColor3f(0.2,0.2,0.2);
	lines = 0;
	glTranslatef(-viewPosition.x,-viewPosition.y,0);
	glBegin(GL_LINES);
	// vertical lines
	int rasterXR = ((int)viewPosition.x + size.x/(2*zoom));
	int rasterXL = ((int)viewPosition.x - size.x/(2*zoom));
	int rasterYU = ((int)viewPosition.y + size.y/(2*zoom));
	int rasterYD = ((int)viewPosition.y - size.y/(2*zoom));
	rasterYD -= rasterYD % gridDeep;
	rasterXL -= rasterXL % gridDeep;
	for(int x = rasterXL; x <= rasterXR; x += gridDeep){
		if(x % 128 == 0){
			glColor3f(0.3,0.1,0.1);
		}else{
			glColor3f(0.2,0.2,0.2);
		}
		glVertex3f(x,( size.y/(2*zoom)+viewPosition.y), 0);
		glVertex3f(x,(-size.y/(2*zoom)+viewPosition.y), 0);
		lines++;		// debug
	}
	// horizontal lines
	
	for(int y = rasterYD; y <= rasterYU; y += gridDeep){
		if(y % 128 == 0){
			glColor3f(0.3,0.1,0.1);
		}else{
			glColor3f(0.2,0.2,0.2);
		}
		glVertex3f(( size.x/(2*zoom)+viewPosition.x), y, 0);
		glVertex3f((-size.x/(2*zoom)+viewPosition.x), y, 0);
	}
	glEnd();
	glTranslatef(viewPosition.x,viewPosition.y,0);
}

void View::addZoomValue(float value){
	if(value > 0){
		zoom += zoom;
	}else{
		zoom -= zoom/2;
	}
	std::cout << "zoom:\t" << zoom << "\tgrid:\t" << gridDeep << "\tlines:\t" << lines << std::endl;
}

void View::moveViewPosition(Vec3 value){
		viewPosition += value * (1.0f/zoom);
}

Player* View::getPlayer(){
	return ePlayer;
}
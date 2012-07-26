#include "View.h"
#include <GL\freeglut.h>
#include <math.h>
#include <iostream>
#include "Editor.h"

using namespace MapEditor;
using namespace GLSL;

int lines = 0; // debug

View::View(ViewModus viewMode, Vec2 position, Vec2 size) : Entity_2D(position, size){
	this->viewMode = viewMode;
	if(viewMode == VIEW_3D) ePlayer = new Player(PLAYER_EDIT);
	zoom = 4;
}

View::~View(void){
}

void View::setUp(){
	
	glMatrixMode(GL_PROJECTION); //old
	glLoadIdentity();			//old
	glViewport((GLsizei)position.x, (GLsizei)position.y, (GLsizei)size.x, (GLsizei)size.y);
	glLoadIdentity();

	glOrtho(-size.x/2, size.x/2, -size.y/2, size.y/2,-65536,65536); // old
	Screen::buildOrthoMatrix(-size.x/2, size.x/2, -size.y/2, size.y/2,-65536,65536);

	glMatrixMode(GL_MODELVIEW);	// old
	glLoadIdentity();			// old
	Screen::ViewMatrix = Matrix4::Identity();

	const float xMin = -size.x/2+1;
	const float xMax =  size.x/2;
	const float yMin = -size.y/2+1;
	const float yMax =  size.y/2;
	// draw Background
	PM::useProg(PROGRAM_NULL);
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

	glScalef(zoom,zoom,zoom); //old
	Screen::ViewMatrix.scale(zoom,zoom,zoom);

	if(viewMode > 0){
		drawGrid();
	}
	

	switch(viewMode){
		case VIEW_TOP:
		{
			glRotatef(0,0,0,0);
			glTranslatef(-viewPosition.x,-viewPosition.y,0);
			Screen::ViewMatrix.rotate(0,0,0,0);
			Screen::ViewMatrix.translate(-viewPosition.x,-viewPosition.y,0);
			break;
		}
		case VIEW_FRONT:
		{
			glRotatef(-90,1,0,0);
			glTranslatef(-viewPosition.x,0,-viewPosition.y);
			Screen::ViewMatrix.rotate(-90,1,0,0);
			Screen::ViewMatrix.translate(-viewPosition.x,0,-viewPosition.y);
			break;
		}
		case VIEW_RIGHT:
		{
			glRotatef(-90,1,0,0);
			glRotatef(90,0,0,1);
			glTranslatef(0, viewPosition.x, -viewPosition.y);
			Screen::ViewMatrix.rotate(-90,1,0,0);
			Screen::ViewMatrix.rotate(90,0,0,1);
			Screen::ViewMatrix.translate(0, viewPosition.x, -viewPosition.y);
			break;
		}
	}
		
	if(viewMode == VIEW_3D){
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		float ar = (float) size.x / (float) size.y;
		PM::useProg(PROGRAM_FOXEL);
		Screen::buildProjectionMatrix(90.0f,ar,1.0f,2048.0f);
		ePlayer->render();
		Screen::updateViewMatix();
		Screen::updateProjMatix();
	}
	PM::useProg(PROGRAM_BASIC);
	Screen::updateViewMatix();
	Screen::updateProjMatix();
	
}

void View::update(float* time){
	if(viewMode == VIEW_3D) ePlayer->update(time);
}

void View::draw(){
	if(viewMode == VIEW_3D){
		PM::useProg(PROGRAM_FOXEL);
	}	
}

void View::drawGrid(){
	glColor3f(0.2f,0.2f,0.2f);
	lines = 0;
	glTranslatef(-viewPosition.x,-viewPosition.y,0);
	glBegin(GL_LINES);
	// vertical lines
	int rasterXR = (int)(viewPosition.x + size.x/(2*zoom));
	int rasterXL = (int)(viewPosition.x - size.x/(2*zoom));
	int rasterYU = (int)(viewPosition.y + size.y/(2*zoom));
	int rasterYD = (int)(viewPosition.y - size.y/(2*zoom));
	rasterYD -= rasterYD % Editor::getGridDeep();
	rasterXL -= rasterXL % Editor::getGridDeep();
	for(int x = rasterXL; x <= rasterXR; x += Editor::getGridDeep()){
		if(x % 128 == 0){
			glColor3f(0.3f,0.1f,0.1f);
		}else{
			glColor3f(0.2f,0.2f,0.2f);
		}
		glVertex3i(x,(int)( size.y/(2*zoom)+viewPosition.y), 0);
		glVertex3i(x,(int)(-size.y/(2*zoom)+viewPosition.y), 0);
		lines++;		// debug
	}
	// horizontal lines
	
	for(int y = rasterYD; y <= rasterYU; y += Editor::getGridDeep()){
		if(y % 128 == 0){
			glColor3f(0.3f,0.1f,0.1f);
		}else{
			glColor3f(0.2f,0.2f,0.2f);
		}
		glVertex3i((int)( size.x/(2*zoom)+viewPosition.x), y, 0);
		glVertex3i((int)(-size.x/(2*zoom)+viewPosition.x), y, 0);
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
	std::cout << "zoom:\t" << zoom << "\tgrid:\t" << Editor::getGridDeep() << "\tlines:\t" << lines << std::endl;
}

void View::moveViewPosition(Vec3 value){
		viewPosition += value * (1.0f/zoom);
}

ViewModus View::getViewMode(){
	return viewMode;
}

Player* View::getPlayer(){
	return ePlayer;
}
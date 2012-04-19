#include "Screen.h"

float Screen::ar = 0;
int Screen::screenWidth = 0;
int Screen::screenHeight = 0;
Matrix4 Screen::ProjMatrix;
Matrix4 Screen::ViewMatrix;

Vec2 Screen::mousePosition = Vec2();
Vec2 Screen::mouseMotion = Vec2();


Screen::Screen(int w, int h, bool isFullscreen)
{
	screenWidth = w;
    screenHeight = h;

	SDL_WM_SetCaption("Foxel Engine", 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  0);

	// Fenster erstellen
	if(isFullscreen){
		screen = SDL_SetVideoMode(screenWidth,screenHeight,32,SDL_HWSURFACE |
		   SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE |
		   SDL_FULLSCREEN);
	}else{
		screen = SDL_SetVideoMode(screenWidth,screenHeight,32,SDL_HWSURFACE |
			   SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE);
	}
	if(screen == NULL){
		std::cout << SDL_GetError();
		getchar();
	}
	
	resize(screenWidth,screenHeight);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void Screen::resize(int w, int h){
	screenWidth = w;
	screenHeight = h;

	ar =(float) screenWidth / (float) screenHeight;

	SDL_UpdateRect(0,0,0,0,0);

	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_TEXTURE_2D);
}

void Screen::load3DView(){
	glEnable(GL_BLEND);
	glViewport(0,0,screenWidth,screenHeight);
	//glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 16000.0); // old
	buildProjectionMatrix(90, ar, 1.0, 1600.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Screen::load2DView(){
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screenWidth, screenHeight);
	glOrtho(0, screenWidth, 0, screenHeight , -128, 128);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Screen::buildProjectionMatrix(float fov, float ratio, float nearPlane, float farPlane) {
 
	float f = 1.0f / tan (fov * ( M_PI / 360.0));
 
	ProjMatrix = Matrix4::Identity();
 
	ProjMatrix.matrix[0] = f / ratio;
	ProjMatrix.matrix[1 * 4 + 1] = f;
	ProjMatrix.matrix[2 * 4 + 2] = (farPlane + nearPlane) / (nearPlane - farPlane);
	ProjMatrix.matrix[3 * 4 + 2] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
	ProjMatrix.matrix[2 * 4 + 3] = -1.0f;
	ProjMatrix.matrix[3 * 4 + 3] = 0.0f;
}

void Screen::catchMousePosition(Vec2 position){
	position.y += Screen::getHeight() - 2 *position.y;
	mousePosition = position;
}

void Screen::catchMouseMotion(Vec2 value){
	value.x *= -1;
	mouseMotion = value;
}

void Screen::reset(){
	mouseMotion.x = 0;
	mouseMotion.y = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::showMouse(){
	SDL_ShowCursor (SDL_ENABLE);
	SDL_WM_GrabInput (SDL_GRAB_OFF);
}

void Screen::hideMouse(){
	SDL_ShowCursor (SDL_DISABLE);
	SDL_WM_GrabInput (SDL_GRAB_ON);
}

SDL_Surface* Screen::getSurface(){
	return screen;
}

GLfloat* Screen::getProjectionMatrix(){
	return ProjMatrix.matrix;
}

GLfloat* Screen::getViewMatrix(){
	return ViewMatrix.matrix;
}

int Screen::getWidth(){
	return screenWidth;
}

int Screen::getHeight(){
	return screenHeight;
}

Vec2 Screen::getMousePosition(){
	return mousePosition;
}

Vec2 Screen::getMouseMotion(){
	return mouseMotion;
}

Screen::~Screen(void)
{
}

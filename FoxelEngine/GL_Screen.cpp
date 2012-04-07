#include "GL_Screen.h"
#include<iostream>

GL_Screen::GL_Screen(int w, int h, bool isFullscreen)
{
	width = w;
	height = h;

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
		screen = SDL_SetVideoMode(width,height,32,SDL_HWSURFACE |
		   SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE |
		   SDL_FULLSCREEN);
	}else{
		screen = SDL_SetVideoMode(width,height,32,SDL_HWSURFACE |
			   SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE);
	}
	if(screen == NULL){
		std::cout << SDL_GetError();
		getchar();
	}
	
	resize(width,height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void GL_Screen::resize(int w, int h){
	width = w;
	height = h;

	ar =(float) width / (float) height;

	SDL_UpdateRect(0,0,0,0,0);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_TEXTURE_2D);
}

void GL_Screen::load3DView(){
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,width,height);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 16000.0);
	glMatrixMode(GL_MODELVIEW);
}

SDL_Surface* GL_Screen::getSurface(){
	return screen;
}

int GL_Screen::getHeight(){
	return height;
}

int GL_Screen::getWidth(){
	return width;
}

GL_Screen::~GL_Screen(void)
{
}

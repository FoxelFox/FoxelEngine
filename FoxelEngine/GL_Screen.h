#pragma once

#include<SDL\SDL.h>
#include<GL\glew.h>
#include<GL\freeglut.h>


class GL_Screen
{
private:
	SDL_Surface* screen;
	float ar;
	int width, height;

public:
	GL_Screen(int w, int h, bool isFullscreen);
	void load3DView();
	void resize(int w, int h);
	int getWidth();
	int getHeight();
	SDL_Surface* getSurface();
	~GL_Screen(void);
};
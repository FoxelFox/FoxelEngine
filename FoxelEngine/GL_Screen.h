#pragma once

#include<SDL\SDL.h>
#include<GL\glew.h>
#include<GL\freeglut.h>
static int screenWidth, screenHeight;
class GL_Screen
{
private:
	SDL_Surface* screen;
	float ar;

public:
	GL_Screen(int w, int h, bool isFullscreen);
	void load3DView();
	void resize(int w, int h);
	static int getWidth();
	static int getHeight();
    static void load2DView();
	SDL_Surface* getSurface();
	~GL_Screen(void);
};
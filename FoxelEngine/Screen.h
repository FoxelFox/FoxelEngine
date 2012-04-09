#pragma once

#include<SDL\SDL.h>
#include<GL\glew.h>
#include<GL\freeglut.h>
#include<iostream>
#include "Vec2.h"


class Screen
{
private:
	SDL_Surface* screen;
	static int screenWidth, screenHeight;
	static Vec2 mousePosition, mouseMotion;
	static float ar;

public:
	Screen(int w, int h, bool isFullscreen);
	~Screen(void);

	void reset();
	void resize(int w, int h);
	void catchMousePosition(Vec2 position);
	void catchMouseMotion(Vec2 value);
	SDL_Surface* getSurface();

	static void load3DView();
	static int getWidth();
	static int getHeight();
	static Vec2 getMousePosition();
	static Vec2 getMouseMotion();
    static void load2DView();
	static void hideMouse();
	static void showMouse();
};
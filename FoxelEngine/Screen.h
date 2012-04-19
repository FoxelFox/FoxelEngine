#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>
#include "Vec2.h"
#include "Matrix4.h"
static double M_PI = 3.14159265358979323846;


class Screen{
private:
	SDL_Surface* screen;
	static int screenWidth, screenHeight;
	static Vec2 mousePosition, mouseMotion;
	static float ar;

public:
	static Matrix4 ProjMatrix;
	static Matrix4 ViewMatrix;
	Screen(int w, int h, bool isFullscreen);
	~Screen(void);

	void reset();
	void resize(int w, int h);
	void catchMousePosition(Vec2 position);
	void catchMouseMotion(Vec2 value);
	SDL_Surface* getSurface();

	static Vec2 getMousePosition();
	static Vec2 getMouseMotion();
	static void buildProjectionMatrix(float fov, float ratio, float near, float far);
    static void load2DView();
	static void load3DView();

	static void hideMouse();
	static void showMouse();

	static GLfloat* getProjectionMatrix();
	static GLfloat* getViewMatrix();

	static int getWidth();
	static int getHeight();
};
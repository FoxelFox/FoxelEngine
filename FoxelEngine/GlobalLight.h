#pragma once
#include <GL\freeglut.h>
#include "Vec3.h"

static GLfloat* ambientLight;
static GLfloat* diffuseLight;
static GLfloat* specularLight;
static GLfloat* mat_specular;
static GLfloat* mat_shininess;

class GlobalLight{
private:

public:
	static void load();
	static void lightAt(Vec3 position);
	static void turnOff();
	static void turnOn();
	GlobalLight(void);
	~GlobalLight(void);
};


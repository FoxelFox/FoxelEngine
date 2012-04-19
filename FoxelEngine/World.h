#pragma once
//#include <GL\freeglut.h>
#include "Event.h"
#include "FoxelManager.h"
#include "Screen.h"
#include "Axes.h"
class World{
private:
	Axes* center;
public:
	World(void);
	void render();
	bool load();
	~World(void);
};


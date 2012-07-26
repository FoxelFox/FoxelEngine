#pragma once
//#include <GL\freeglut.h>
#include <vector>
#include "Event.h"
#include "FoxelManager.h"
#include "Screen.h"
#include "Axes.h"
#include "Bullet.h"
#include "GameGUI.h"
#include "Config.h"

class World{
private:
	Axes* center;
	GameGUI* gui;
	BulletManager* bulletManager;

public:
	World(void);
	void render();
	void drawGui();
	void update();
	bool load();
	void setDebugMode(bool boolean);
	~World(void);
};


#pragma once
#include "FoxelManager.h"
class World{
	
public:
	FoxelManager* foxelManager;
	World(void);
	void render();
	void init();
	~World(void);
};


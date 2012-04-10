#include "World.h"


World::World(void){
	//foxelManager = new FoxelManager();
}

void World::init(){
	//foxelManager->setupFoxels();
}

void World::render(){
	FoxelManager::render();
}

World::~World(void){
	FoxelManager::deleteAll();
}

#include "World.h"


World::World(void){
	foxelManager = new FoxelManager();
}

void World::init(){
	//foxelManager->setupFoxels();
}

void World::render(){
	foxelManager->render();
}

World::~World(void){
	foxelManager->deleteAll();
}

#include "World.h"

using namespace GLSL;

World::World(void){
	center = new Axes();
}

bool World::load(){
	Vec3d* test = new Vec3d(2.0,2.0,2.0);
	new Event::setFoxel(test,1);
	center->load();
	return true;
}

void World::render(){
	Screen::updateViewMatix();

	FoxelManager::render();
	glutSolidSphere(4,32,16);
	center->render();

	
	
}

World::~World(void){
	FoxelManager::deleteAll();
}

#include "World.h"
#include "Map.h"

using namespace GLSL;

World::World(void){
	center = new Axes();
	bulletManager = new BulletManager();
	gui = new GameGUI();

}

bool World::load(){
	
	if(Map::load("Test_Map")){
		
	}
	center->load();
	return true;
}

void World::update(){
	bulletManager->detectHits();
	Map::update();

	if(Config::isDebug()){
		gui->setDebugChunkInformation(FoxelManager::getNumberOfCurrentChunkUpdates());
		gui->setDebugPolycountInformation(FoxelManager::getPolyCount());
		gui->setDebugGpuUploads(FoxelManager::getNumberOfPendingGpuUploads());
		gui->setDebugDirectLightsCount(FoxelManager::getNumberOfDirectLights());
		gui->setDebugBounceLightsCount(FoxelManager::getNumberOfBounceLights());
		gui->update();
	}
}

void World::render(){
	Screen::updateViewMatix();

	FoxelManager::render();
	
	PM::useProg(PROGRAM_MODEL);
	Screen::updateProjMatix();
	Screen::updateViewMatix();
	center->render();
}

void World::drawGui(){
	PM::useProg(PROGRAM_NULL);
	if(Config::isDebug()) gui->draw();
}

World::~World(void){
	delete gui;
}
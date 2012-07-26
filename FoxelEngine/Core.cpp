#include "Core.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace GLSL;

Core::Core(){
	running = false;
	userState = ON_MAIN_MENU;
	config = new Config();
	sdlEvent = new SDL_Event();
	player = NULL;
	world = NULL;

	debugMode = true;
	tickrate = 32;
	tick = 0;
}

bool Core::init(int argc, char *argv[]){
	config->readConfig("config.cfg");
	//world->init();

	// SDL Initialisieren
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cout << "SDL konnte nicht initialisiert werden: " << SDL_GetError() << "\n";
		getchar();
		return false;
	}else{
		screen = new Screen(config->getScreenW(),config->getScreenH(), config->isFullscreen());
		// GLEW INIT
		GLenum err = glewInit();
		glutInit(&argc,argv);
		if (GLEW_OK != err){
			std::cout << "Error: " << glewGetErrorString(err)
			<< std::endl;
		}
		cout << "Using GLEW " << glewGetString(GLEW_VERSION) << "\n\n";

		mainMenu = new Main_Menu();
		Event::BasicEvent::initEventSystem();
		PM::useProg(PROGRAM_BASIC);
		PM::useProg(PROGRAM_NULL);
		FoxelManager::startChunkThreads(Config::getChunkThreads());
		running = true;
		return true;
	}
}

void Core::startGame(){
	userState = ON_GAME;
	postPro = new PostProcessor();
	delete world;
	delete player;

	player = new Player(PLAYER_FOX);
	world = new World();

	screen->hideMouse();

	// load data
	postPro->load();
	world->load();
}

void Core::startEditor(){
	userState = ON_EDIT;
	//delete world, player;
	editor = new MapEditor::Editor();
}

void Core::update(float* time){
	tick += *time;
	switch(userState){
		case ON_GAME:
			player->update(time);
			if(tick > tickrate){
				world->update();
				tick = 0;
			}
			break;
		case ON_GAME_PAUSE:
			player->update(time);
			mainMenu->update();
			break;
		case ON_MAIN_MENU:  mainMenu->update(); break;
		case ON_EDIT:       editor->update(time); break;
	}
}

void Core::render(){
	screen->reset();
	switch(userState){
		//========================================#
		case ON_GAME:       	PM::useProg(PROGRAM_FOXEL);
								screen->load3DView();
								postPro->setupToDraw();
								player->render();
								world->render();
								postPro->draw();
								world->drawGui();
								break;
		//========================================#
		case ON_MAIN_MENU:      //PM::useProg(PROGRAM_FOXEL);
								screen->load3DView();
								mainMenu->draw();
								break;
							
		//========================================#
		case ON_GAME_PAUSE:     PM::useProg(PROGRAM_FOXEL);
								screen->load3DView();
								player->render();
								world->render(); 
								PM::useProg(PROGRAM_NULL);
								mainMenu->draw();
								break;
							
		//========================================#
		case ON_EDIT:           editor->draw();
								break;
		//========================================#
	}
	screen->swap();
}

Core::~Core(void){
}
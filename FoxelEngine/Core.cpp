#include "Core.h"
#include <iostream>

Core::Core(){
	running = false;
	userState = ON_MAIN_MENU;
	config = new Config();
	sdlEvent = new SDL_Event();
	axes = new Axes();
}

bool Core::init(int argc, char *argv[]){
	config->readConfig("config.cfg");
	mainMenu = new Main_Menu();
	mainMenu->setScreenSize(config->getScreenW(),config->getScreenH());
	//world->init();

	// SDL Initialisieren
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cout << "SDL konnte nicht initialisiert werden: " << SDL_GetError() << "\n";
		getchar();
		return false;
	}else{
		screen = new GL_Screen(config->getScreenW(),config->getScreenH(), config->isFullscreen());
		// GLEW INIT
		GLenum err = glewInit();
		glutInit(&argc,argv);
		if (GLEW_OK != err){
			std::cout << "Error: " << glewGetErrorString(err)
			<< std::endl;
		}
		std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << "\n\n";

		Event::BasicEvent::initEventSystem();
		running = true;
		return true;
	}
}

void Core::startGame(){
	userState = ON_GAME;
	world = new World();
	player = new Player();
	SDL_ShowCursor (SDL_DISABLE);
	SDL_WM_GrabInput (SDL_GRAB_ON);
}

void Core::startEditor(){
	userState = ON_EDIT;
	delete world, player;
	editor = new Editor();
}

void Core::update(float* time){
	if(userState == ON_GAME || userState == ON_GAME_PAUSE){
		player->update(time);
	}
	if(userState == ON_EDIT){
		
	}
}

void Core::render(){
	
	switch(userState){
		//========================================#
		case ON_GAME:			screen->load3DView();
								player->render();
								world->render();  
								axes->render();
								break;							
		//========================================#
		case ON_MAIN_MENU:		screen->load3DView();
								mainMenu->draw();
								break;
							
		//========================================#
		case ON_GAME_PAUSE:		screen->load3DView();
								mainMenu->draw();
								
								break;
							
		//========================================#
		case ON_EDIT:			
								editor->draw();
								break;
		//========================================#
	}
	SDL_GL_SwapBuffers();
}

Core::~Core(void){
}

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
		std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << "\n\n";

        mainMenu = new Main_Menu();
		Event::BasicEvent::initEventSystem();
		running = true;
		return true;
	}
}

void Core::startGame(){
	userState = ON_GAME;
	world = new World();
	delete player;
	player = new Player(PLAYER_NORMAL);
	player->setTyp(PLAYER_FOX);				// debug
	screen->hideMouse();
}

void Core::startEditor(){
	userState = ON_EDIT;
	delete world, player;
	editor = new MapEditor::Editor();
}

void Core::update(float* time){
	switch(userState){
    case ON_GAME:       player->update(time); break;
    case ON_GAME_PAUSE: player->update(time); break;
    case ON_MAIN_MENU:                        break;
    case ON_EDIT:       editor->update(time); break;
    }
}

void Core::render(){
	screen->reset();
	switch(userState){
		//========================================#
		case ON_GAME:           screen->load3DView();
                                player->render();
                                world->render();  
                                axes->render();
                                break;							
		//========================================#
		case ON_MAIN_MENU:      screen->load3DView();
                                mainMenu->draw();
                                break;
							
		//========================================#
		case ON_GAME_PAUSE:     screen->load3DView();
                                mainMenu->draw();
								
                                break;
							
		//========================================#
		case ON_EDIT:           editor->draw();
                                break;
		//========================================#
	}
	SDL_GL_SwapBuffers();
}

Core::~Core(void){
}

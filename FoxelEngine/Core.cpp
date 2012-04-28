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

		// extensions
		//fstream f;
		//f.open("Extensions.log", ios::out);
		//f << glGetString(GL_EXTENSIONS) << endl;
		//f.close();

		testing();


        mainMenu = new Main_Menu();
		Event::BasicEvent::initEventSystem();
		PM::useProg(PROGRAM_BASIC);
		PM::useProg(PROGRAM_NULL);
		GlobalLight::load();
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

	// load data
	world->load();;
}

void Core::startEditor(){
	userState = ON_EDIT;
	//delete world, player;
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
		case ON_GAME:       	PM::useProg(PROGRAM_FOXEL);
								screen->load3DView();
								player->render();
                                world->render();
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

// Testing Area
void Core::testing(){
	float A[] = {1,2,0,1,
		         0,0,3,0,
			     1,0,2,0,
				 0,0,0,2};
	float B[] = {0,1,0,2,
		         0,3,1,0,
			     2,0,2,0,
				 1,0,1,0};
	
	Matrix4 mA(A);
	Matrix4 mB(B);

	Matrix4 erg(mB*mA);
	erg.printMatrix();
}
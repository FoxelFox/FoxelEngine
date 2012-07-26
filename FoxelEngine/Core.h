#pragma once
#include <iostream>// for Debug infos

#include "Event.h"
#include "Screen.h"
#include "World.h"
#include "Player.h"
#include "Config.h"
#include "Main_Menu.h"
#include "Editor.h"
#include "PostProcessor.h"


enum{ON_MAIN_MENU = 0, ON_GAME = 1, ON_EDIT = 2, ON_GAME_PAUSE = 3};

class Core
{
private:
	Config* config;
	Screen* screen;
	SDL_Event* sdlEvent;
	World* world;
	Player* player;
	Main_Menu* mainMenu;
	MapEditor::Editor* editor;
	PostProcessor* postPro;

	float tickrate, tick;
	int userState;
	bool debugMode;

	void startGame();
	void startEditor();
	void inputOnGame();
	void inputOnMenu();
	void inputOnEdit();
	void specialInputs();

public:
	bool running;


	Core(void);
	bool init(int argc, char *argv[]);
	void inputs();
	void events();
	void update(float* time);
	void render();
	~Core(void);
};


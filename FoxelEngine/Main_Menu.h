#pragma once
#include "GL_Screen.h"
#include "gamemenu.h"
#include "Event.h"
class Main_Menu : public GameMenu{
private:
	void createEvents();
public:
	void draw();
	Main_Menu(void);
	~Main_Menu(void);
};


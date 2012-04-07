#pragma once
#include "gamemenu.h"
class Main_Menu : public GameMenu{
private:
	void createEvents();
public:
	void draw();
	Main_Menu(void);
	~Main_Menu(void);
};


#pragma once
#include "GameMenu.h"
class ToolBox : public GameMenu{
public:
	ToolBox(Vec2 position, Vec2 size);
	~ToolBox(void);
    void draw();
};


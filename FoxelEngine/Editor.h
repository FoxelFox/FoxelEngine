#pragma once
#include <vector>
#include "View.h"
#include "GameMenu.h"
#include "ToolBox.h"


class Editor : public GameMenu{
	float b;			// Border
	ToolBox* toolBox;
	std::vector<MapEditor::View*> views;

public:
	void draw();
	void catchMousePosition(Vec2 pos);
	void catchMouseClick(Vec2 pos);
    void resize();
	Editor(void);
	~Editor(void);
};


#pragma once
#include <vector>
#include "Screen.h"
#include "TextButton.h"
#include "Entity_2D.h"
class GameMenu : public Entity_2D{
protected:
	std::vector<TextButton> selectOptions;
public:
	GameMenu(Vec2 position, Vec2 size);
	GameMenu(void);
	~GameMenu(void);
	virtual void createEvents();
	void catchMousePosition(Vec2 pos);
	void catchMouseClick(Vec2 pos);
	void update();
	void draw();
};
#pragma once
#include <vector>
#include "TextButton.h"
#include "Entity_2D.h"
class GameMenu : public Entity_2D{
protected:
	int screenWidth, screenHeight;
	std::vector<TextButton> selectOptions;
public:
	GameMenu(Vec2 position, Vec2 size);
	GameMenu(void);
	~GameMenu(void);
	virtual void createEvents();
	void catchMousePosition(Vec2 pos);
	void catchMouseClick(Vec2 pos);
	void setScreenSize(int w, int h);
	void draw();
};
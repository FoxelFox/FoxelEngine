#pragma once
#include "Entity_2D.h"
#include "Color.h"
#include "SlideControl.h"
class ColorPanel : public Entity_2D{
private:
	Color color;
	SlideControl* slider_red;
	SlideControl* slider_green;
	SlideControl* slider_blue;
	SlideControl* slider_emit;

	void drawColorCircle();
public:
	ColorPanel(Vec2 position, Vec2 size);
	~ColorPanel(void);

	Color getColor();
	void draw();
	void resize(Vec2 position);
	void mouseInteraction();
};


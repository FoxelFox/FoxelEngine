#pragma once
#include "gamecomponent.h"
class DrawableGameComponent :
	public GameComponent
{
protected:
	unsigned int anzVertex;
	unsigned int anzPolygon;

public:
	DrawableGameComponent(void);
	~DrawableGameComponent(void);
};


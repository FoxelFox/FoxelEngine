#pragma once
#include "Vec3d.h"
class GameComponent{
protected:
	Vec3d position;
public:
	GameComponent(void);
	virtual void update();
	~GameComponent(void);
};
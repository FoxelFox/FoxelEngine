#pragma once
#include "GameComponent.h"
#include "Vec3d.h"

class PropDynamic : public GameComponent{
protected:
	float friction;
	Vec3d velocity;
	Vec3d rotation;

public:
	PropDynamic(void);
	PropDynamic(Vec3d position);
	void update(float* time);
	~PropDynamic(void);

	void setFriction(float friction);
	void setRotation(Vec3d rotation);
	void setPosition(Vec3d position);
};


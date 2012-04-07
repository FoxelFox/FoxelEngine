#pragma once
#include <SDL\SDL.h>
#include <math.h>
#include "PropDynamic.h"
#include "Camera.h"
#include "PlayerControler.h"
#include "Vec3.h"
#include "Convert.h"
#include "Foxel_Interaction.h"

class Player : public PropDynamic{
private:
	Camera* camera;
	PlayerControler* controler;

	// propertys
	float maxMoveSpeed;
	float accelerateValue;

	void createEvents();
public:
	Player(void);
	Player(Vec3d position);
	void catchKeyDown(SDLKey sym);
	void catchKeyUp(SDLKey sym);
	void catchMouseMotion(float x, float y);
	void update(float* time);
	void render();
	~Player(void);
};


#pragma once
#include <SDL\SDL.h>
#include <math.h>
#include "PropDynamic.h"
#include "Camera.h"
#include "PlayerControler.h"
#include "Vec3.h"
#include "Convert.h"
#include "Foxel_Interaction.h"

enum PlayerTyp { PLAYER_NORMAL = 1, PLAYER_EDIT = 2, PLAYER_FOX = 1337};

class Player : public PropDynamic{
private:
	Camera* camera;
	PlayerControler* controler;

	// propertys
	float maxMoveSpeed;
	float accelerateValue;
	int playerTyp;

	short health;
	short armor;

	bool noclip;


	void createEvents();
public:
	Player(int typ);
	Player(Vec3d position);
	void setTyp(int typ);
	void catchKeyDown(SDLKey sym);
	void catchKeyUp(SDLKey sym);
	void catchMouseMotion(float x, float y);
	void update(float* time);
	void render();
	~Player(void);
};


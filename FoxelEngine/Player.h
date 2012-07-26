#pragma once
#include <SDL\SDL.h>
#include <math.h>
#include "PropDynamic.h"
#include "Camera.h"
#include "PlayerControler.h"
#include "Pistol.h"
#include "Vec3.h"
#include "Convert.h"
#include "Foxel_Interaction.h"

enum PlayerTyp { PLAYER_NORMAL = 1, PLAYER_EDIT = 2, PLAYER_FOX = 1337};

class Player : public PropDynamic{
private:
	Pistol* pistol;
	Camera* camera;
	PlayerControler* controler;

	// propertys
	float maxMoveSpeed;
	float accelerateValue;
	float drx,dry;
	int playerTyp;
	
	short health;
	short armor;

	bool noclip;

	Vec3 calcDirVector();
	void createEvents();
public:
	Player(int typ);
	void setTyp(int typ);
	void catchKeyDown(SDLKey sym);
	void catchKeyUp(SDLKey sym);
	void catchMouseMotion(float x, float y);
	PlayerControler* getControler();
	void update(float* time);
	void render();
	~Player(void);
};


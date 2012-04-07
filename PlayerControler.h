#pragma once
#include <SDL\SDL.h>
class PlayerControler{
friend class Player;
private:
	bool left, right;
	bool forward, backward;
	bool sprint;
	bool setFoxel;

public:
	PlayerControler(void);
	void getKeyDown(SDLKey sym);
	void getKeyUp(SDLKey sym);
	~PlayerControler(void);
};


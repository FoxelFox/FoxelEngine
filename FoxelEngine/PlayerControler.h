#pragma once
#include <SDL\SDL.h>
class PlayerControler{
friend class Player;
private:
	int controleMode;

	bool left, right;
	bool forward, backward;
	bool sprint;
	bool setFoxel;

public:
	PlayerControler(int controleMode);
	void getKeyDown(SDLKey sym);
	void getKeyUp(SDLKey sym);
	~PlayerControler(void);
};


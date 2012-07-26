#pragma once
#include <SDL\SDL.h>
class PlayerControler{
friend class Player;
private:
	unsigned char nlod;	//DEBUG! level of detail for chunks 
	int controleMode;
	int wheelState;
	bool left, right;
	bool forward, backward;
	bool sprint;
	bool setFoxel,shoot,zoom,midleMouseButton;

public:
	PlayerControler(int controleMode);
	void getKeyDown(SDLKey sym);
	void getKeyUp(SDLKey sym);
	void catchMouseClick(Uint8 button);
	void catchMouseRelease(Uint8 button);
	~PlayerControler(void);
};


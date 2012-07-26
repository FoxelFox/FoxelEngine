#include "PlayerControler.h"
#include "Player.h"
#include <math.h>

PlayerControler::PlayerControler(int controleMode){
	this->controleMode = controleMode;
	left = right = false;
	forward = backward = false;
	sprint = false;
	setFoxel = false;
	shoot = false;
	zoom = false;
	nlod = 1;
	wheelState = 0;
	midleMouseButton = false;
}

void PlayerControler::getKeyDown(SDLKey sym){
	switch(sym){
		case SDLK_a: left = true; break;
		case SDLK_d: right = true; break;
		case SDLK_w: forward = true; break;
		case SDLK_s: backward = true; break;
		case SDLK_LSHIFT: sprint = true; break;
		case SDLK_e: setFoxel = true; break;
	}
}

void PlayerControler::getKeyUp(SDLKey sym){
	switch(sym){
		case SDLK_a: left = false; break;
		case SDLK_d: right = false; break;
		case SDLK_w: forward = false; break;
		case SDLK_s: backward = false; break;
		case SDLK_LSHIFT: sprint = false; break;
		case SDLK_e: setFoxel = false; break;
	}
}

void PlayerControler::catchMouseClick(Uint8 button){
	switch(button){
	case SDL_BUTTON_LEFT: shoot = true; break;
	case SDL_BUTTON_MIDDLE: midleMouseButton = true; break;
	case SDL_BUTTON_RIGHT: zoom = true; break;

	case SDL_BUTTON_WHEELDOWN: 
		wheelState--;
		if(nlod > 1){
			nlod /= 2;
			FoxelManager::setGlobalLod(nlod);
		}
		break;
	case SDL_BUTTON_WHEELUP:
		wheelState++;
		if(nlod < 8){
			nlod *= 2;
			FoxelManager::setGlobalLod(nlod);
		}
		break;
	}
}

void PlayerControler::catchMouseRelease(Uint8 button){
	switch(button){
	case SDL_BUTTON_LEFT: shoot = false; break;
	case SDL_BUTTON_MIDDLE: midleMouseButton = false; break;
	case SDL_BUTTON_RIGHT: zoom = false; break;
	}
}


PlayerControler::~PlayerControler(void)
{
}

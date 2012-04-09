#include "PlayerControler.h"


PlayerControler::PlayerControler(int controleMode){
	this->controleMode = controleMode;
	left = right = false;
	forward = backward = false;
	sprint = false;
	setFoxel = false;
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

PlayerControler::~PlayerControler(void)
{
}

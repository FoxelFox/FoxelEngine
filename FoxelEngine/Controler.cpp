#include "Controler.h"
#include "Screen.h"

using namespace MapEditor;
Controler::Controler(void){
	rightMouseButton = leftMouseButton = midleMouseButton = false;
	wheelState = 0;
	A = S = D = W = Shift = Tab = Grab = false;
}


Controler::~Controler(void)
{
}

void Controler::catchKeyDown(SDLKey sym){
	switch(sym){
		case SDLK_a: A = true; break;
		case SDLK_d: D = true; break;
		case SDLK_w: W = true; break;
		case SDLK_s: S = true; break;
		case SDLK_TAB: Tab = true; break;
		case SDLK_LSHIFT: Shift = true; break;

		case SDLK_f: 
			if(Grab){ 
				Grab = false;
				Screen::showMouse();
			}
			else{
				Grab = true;
			}
			break;
	}
}

void Controler::catchKeyUp(SDLKey sym){
	switch(sym){
		case SDLK_a: A = false; break;
		case SDLK_d: D = false; break;
		case SDLK_w: W = false; break;
		case SDLK_s: S = false; break;
		case SDLK_TAB: Tab = false; break;
		case SDLK_LSHIFT: Shift = false; break;
	}
}

void Controler::catchMouseClick(Uint8 button){
	switch(button){
	case SDL_BUTTON_LEFT: leftMouseButton = true; break;
	case SDL_BUTTON_MIDDLE: midleMouseButton = true; break;
	case SDL_BUTTON_RIGHT: rightMouseButton = true; break;

	case SDL_BUTTON_WHEELDOWN: wheelState--; break;
	case SDL_BUTTON_WHEELUP: wheelState++; break;
	}
}

void Controler::catchMouseRelease(Uint8 button){
	switch(button){
	case SDL_BUTTON_LEFT: leftMouseButton = false; break;
	case SDL_BUTTON_MIDDLE: midleMouseButton = false; break;
	case SDL_BUTTON_RIGHT: rightMouseButton = false; break;
	}
}
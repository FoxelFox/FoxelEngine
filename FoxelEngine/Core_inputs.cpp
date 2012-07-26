#include"Core.h"

void Core::inputs(){

	/* Schau nach, ob Events anliegen */
	while (SDL_PollEvent (sdlEvent)){  /* Solange noch Events vorhanden sind */
		
		specialInputs();
		switch(userState){
			case ON_GAME:		inputOnGame();
								break;
		
			case ON_MAIN_MENU:	inputOnMenu();
								break;

			case ON_GAME_PAUSE: inputOnMenu();
								break;

			case ON_EDIT:		inputOnEdit();
								break;
		}
	}			
}

void Core::specialInputs(){
	switch (sdlEvent->type){
		case SDL_QUIT:
			exit (0);
			break;

		case SDL_KEYDOWN:  /* Tastaturevent */
			switch(sdlEvent->key.keysym.sym){
				case SDLK_F1: config->switchDebugMode(); break;
				case SDLK_F2: config->setDisplayMode(DisplayMode::DISPLAY_QUAD); break;
				case SDLK_F3: config->setDisplayMode(DisplayMode::DISPLAY_WITHOUT_RAD); break;
				case SDLK_F4: config->setDisplayMode(DisplayMode::DISPLAY_NORMAL); break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:  /* Tastaturevent */
			switch(sdlEvent->button.button){
				case SDL_BUTTON_LEFT: screen->setKlickLeft(true); break;
				case SDL_BUTTON_RIGHT: screen->setKlickRight(true); break;
				default: break;
			}
			break;

		case SDL_MOUSEBUTTONUP:  /* Tastaturevent */
			switch(sdlEvent->button.button){
				case SDL_BUTTON_LEFT: screen->setKlickLeft(false); break;
				case SDL_BUTTON_RIGHT: screen->setKlickRight(false); break;
				default: break;
			}
			break;

		case SDL_MOUSEMOTION:
			screen->catchMousePosition(Vec2(sdlEvent->motion.x, sdlEvent->motion.y));
			screen->catchMouseMotion(Vec2(sdlEvent->motion.xrel, sdlEvent->motion.yrel));
			break;

		case SDL_VIDEORESIZE:	
			screen->resize(sdlEvent->resize.w,sdlEvent->resize.h);
			if(userState == ON_EDIT){    editor->resize();}
			break;
	}
}
void Core::inputOnGame(){
	switch (sdlEvent->type)
	{  /* Schau nach, welcher Event eingetroffen ist */
	case SDL_KEYDOWN:  /* Tastaturevent */
		switch(sdlEvent->key.keysym.sym){
			case SDLK_ESCAPE:
				userState = ON_GAME_PAUSE;
				screen->showMouse();
				break;
		}
		player->catchKeyDown(sdlEvent->key.keysym.sym);
		break;

	case SDL_KEYUP:  /* Tastaturevent */
		player->catchKeyUp(sdlEvent->key.keysym.sym);		
		break;

	case SDL_MOUSEMOTION: /* Mausevent */
		player->catchMouseMotion(sdlEvent->motion.xrel, sdlEvent->motion.yrel);
		break;

	case SDL_MOUSEBUTTONDOWN:
		player->getControler()->catchMouseClick(sdlEvent->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		player->getControler()->catchMouseRelease(sdlEvent->button.button);
		break;

	default: /* unbeachteter Event */
		break;
	}
}
void Core::inputOnMenu(){
switch (sdlEvent->type){
	case SDL_KEYDOWN:  /* Tastaturevent */
		switch(sdlEvent->key.keysym.sym){
			case SDLK_ESCAPE:
				running = false; break;
		}
		break;

	case SDL_KEYUP:		
		break;

	default: /* unbeachteter Event */
		break;
	}
}
void Core::inputOnEdit(){
switch (sdlEvent->type){
	case SDL_KEYDOWN:  /* Tastaturevent */
		switch(sdlEvent->key.keysym.sym){
			case SDLK_ESCAPE: userState = ON_MAIN_MENU;
				screen->showMouse();
		}
		editor->catchKeyDown(sdlEvent->key.keysym.sym);
		break;

	case SDL_KEYUP:
		editor->catchKeyUp(sdlEvent->key.keysym.sym);
		break;

	case SDL_MOUSEBUTTONDOWN:
		editor->getControler()->catchMouseClick(sdlEvent->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		editor->getControler()->catchMouseRelease(sdlEvent->button.button);
		break;

	default: /* unbeachteter Event */
		break;
	}
}
#include"Core.h"

void Core::inputs(){
	bool done = false;
	
	/* Schau nach, ob Events anliegen */
	while ((!done) && SDL_PollEvent (sdlEvent)){  /* Solange noch Events vorhanden sind */
		
		specialInputs(&done);
		switch(userState){
			case ON_GAME:		inputOnGame();
								done = true; break;
		
			case ON_MAIN_MENU:	inputOnMenu();
								done = true; break;

			case ON_GAME_PAUSE: inputOnMenu();
								done = true; break;

			case ON_EDIT:		inputOnEdit();
								done = true; break;
		}
	}			
}

void Core::specialInputs(bool* done){
	switch (sdlEvent->type){
		case SDL_QUIT:
			exit (0);
			break;

		case SDL_MOUSEMOTION:
			screen->catchMousePosition(Vec2(sdlEvent->motion.x, sdlEvent->motion.y));
			screen->catchMouseMotion(Vec2(sdlEvent->motion.xrel, sdlEvent->motion.yrel));
			break;

		case SDL_VIDEORESIZE:	
			screen->resize(sdlEvent->resize.w,sdlEvent->resize.h);
            if(userState == ON_EDIT){    editor->resize();}
			*done = true;
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

	case SDL_MOUSEMOTION:
		mainMenu->catchMousePosition(Vec2(sdlEvent->motion.x, sdlEvent->motion.y));
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch(sdlEvent->button.button){
			case SDL_BUTTON_LEFT:
				mainMenu->catchMouseClick(Vec2(sdlEvent->motion.x,sdlEvent->motion.y));
		}
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
#include"Core.h"

void Core::inputs(){
	bool done = false;
	
	/* Schau nach, ob Events anliegen */
	while ((!done) && SDL_PollEvent (sdlEvent)){  /* Solange noch Events vorhanden sind */
		
		specialEvents(&done);
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

void Core::specialEvents(bool* done){
	switch (sdlEvent->type){
		case SDL_QUIT:
			exit (0);
			break;

		case SDL_VIDEORESIZE:	
			screen->resize(sdlEvent->resize.w,sdlEvent->resize.h);
			mainMenu->setScreenSize(screen->getWidth(),screen->getHeight());
			if(editor != NULL) editor->setScreenSize(screen->getWidth(),screen->getHeight());
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
				SDL_ShowCursor (SDL_ENABLE);
				SDL_WM_GrabInput (SDL_GRAB_OFF);
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
		}
		break;

	case SDL_KEYUP:		
		break;

	case SDL_MOUSEMOTION:
		editor->catchMousePosition(Vec2(sdlEvent->motion.x, sdlEvent->motion.y));
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch(sdlEvent->button.button){
			case SDL_BUTTON_LEFT:
				editor->catchMouseClick(Vec2(sdlEvent->motion.x,sdlEvent->motion.y));
		}
	default: /* unbeachteter Event */
		break;
	}
}
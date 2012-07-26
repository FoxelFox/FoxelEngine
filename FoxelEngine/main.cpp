#include "Core.h"
#include <SDL\SDL.h>
Core game;
#undef main
int main(int argc, char *argv[]){
	if(game.init(argc,argv)){
		float startTime, endTime, renderTime = 0;
		while(game.running){
			startTime = (float) SDL_GetTicks();
			game.inputs();
			game.events();
			game.update(&renderTime);
			game.render();
			endTime = (float) SDL_GetTicks();
			renderTime = (endTime - startTime);

		}
	}
	return 0;
}
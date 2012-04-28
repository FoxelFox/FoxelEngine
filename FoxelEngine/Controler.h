#pragma once
#include <SDL\SDL.h>

namespace MapEditor{
	class Controler{
		friend class Editor;
	private:
		bool rightMouseButton, leftMouseButton, midleMouseButton;
		bool A,S,D,W,Shift,Tab;
		bool Grab;
		int wheelState;

	public:
		Controler(void);
		~Controler(void);
		void catchKeyDown(SDLKey sym);
		void catchKeyUp(SDLKey sym);
		void catchMouseClick(Uint8 button);
		void catchMouseRelease(Uint8 button);
	};
}


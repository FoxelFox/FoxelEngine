#pragma once
#include <vector>
#include "View.h"
#include "GameMenu.h"
#include "ToolBox.h"
#include "Controler.h"

namespace MapEditor{
	class Editor : public GameMenu{
	private:
		ToolBox* toolBox;
		Controler* controler;
		std::vector<View*> views;
		View* catchActiveView();
		bool playMode;

	public:
		void draw();
		void update(float* time);
		void catchMouseClick(Vec2 pos);
		void catchKeyDown(SDLKey sym);
		void catchKeyUp(SDLKey sym);
		void resize();
		MapEditor::Controler* getControler();
		Editor(void);
		~Editor(void);
	};
}

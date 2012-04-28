#pragma once
#include <vector>
#include "View.h"
#include "Axes.h"
#include "GameMenu.h"
#include "ToolBox.h"
#include "Controler.h"
#include "BrushBox.h"

namespace MapEditor{
	class Editor : public GameMenu{
	private:
		ToolBox* toolBox;
		Controler* controler;
		std::vector<View*> views;
		View* activeView;
		View* catchActiveView();
		Axes* center;
		BrushBox* brush;
		bool playMode;
		static int gridDeep;

	public:
		Editor(void);
		~Editor(void);

		void draw();
		void update(float* time);
		void catchMouseClick(Vec2 pos);
		void catchKeyDown(SDLKey sym);
		void catchKeyUp(SDLKey sym);
		void resize();
		MapEditor::Controler* getControler();
		static int getGridDeep();
	};
}

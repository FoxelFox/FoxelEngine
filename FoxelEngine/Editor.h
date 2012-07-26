#pragma once
#include <vector>
#include "View.h"
#include "Axes.h"
#include "GameMenu.h"
#include "ToolBox.h"
#include "Controler.h"
#include "BrushBox.h"
#include "ColorPanel.h"

namespace MapEditor{
	class Editor : public GameMenu{
	private:
		ToolBox* toolBox;
		Controler* controler;
		std::vector<View*> views;
		View* activeView;
		View* catchActiveView();
		Axes* center;
		ColorPanel* colorPanel;
		BrushBox* brush;
		bool playMode;
		static int gridDeep;
		void save();

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

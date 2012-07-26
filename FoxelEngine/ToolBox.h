#pragma once
#include "GameMenu.h"
namespace MapEditor{

	enum ActiveTool {Brush , Entity};

	class ToolBox : public GameMenu{
	public:
		ToolBox(Vec2 position, Vec2 size);
		~ToolBox(void);
		ActiveTool activeTool;
		void update();
		void draw();
		void resize();
	};
}


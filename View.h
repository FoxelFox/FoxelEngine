#pragma once
#include <gl\glew.h>
#include "Entity_2D.h"
#include "Axes.h"

namespace MapEditor{
	enum {VIEW_3D = 0, VIEW_TOP = 1, VIEW_RIGHT = 2, VIEW_FRONT = 3};

	class View : Entity_2D{
		char viewMode;
		Axes axes;
	public:
		View(char viewMode, Vec2 position, Vec2 size);
		~View(void);
		void setSize(Vec2 size);
		void setUp();
		void draw();

		Vec2 getSize();
	};
}

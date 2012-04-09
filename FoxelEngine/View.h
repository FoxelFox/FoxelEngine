#pragma once
#include <gl\glew.h>
#include "Entity_2D.h"
#include "Axes.h"
#include "Vec3.h"
#include "Player.h"
namespace MapEditor{
	enum {VIEW_3D = 0, VIEW_TOP = 1, VIEW_RIGHT = 2, VIEW_FRONT = 3};

	class View : public Entity_2D{
	private:
		char viewMode;
		Vec3 viewPosition;
		Player* ePlayer;
		float zoom;
		Axes axes;
		int gridDeep;
		void drawGrid();
	public:
		View(char viewMode, Vec2 position, Vec2 size);
		~View(void);
		void setUp();
		void update(float* time);
		void draw();
		Player* getPlayer();
		void addZoomValue(float value);
		void moveViewPosition(Vec3 value);
	};
}

#pragma once
#include <gl\glew.h>
#include "Entity_2D.h"
#include "ShaderProgram.h"
#include "Screen.h"
#include "Vec3.h"
#include "Player.h"
namespace MapEditor{
	enum ViewModus {VIEW_3D = 0, VIEW_TOP = 1, VIEW_RIGHT = 2, VIEW_FRONT = 3};

	class View : public Entity_2D{
		friend class Editor;
	private:
		ViewModus viewMode;
		Vec3 viewPosition;
		Player* ePlayer;
		float zoom;
		void drawGrid();
	public:
		View(ViewModus viewMode, Vec2 position, Vec2 size);
		~View(void);
		void setUp();
		void update(float* time);
		void draw();
		Player* getPlayer();
		void addZoomValue(float value);
		void moveViewPosition(Vec3 value);

		ViewModus getViewMode();
	};
}

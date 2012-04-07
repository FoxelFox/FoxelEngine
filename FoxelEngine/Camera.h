#pragma once
#include <GL\glew.h>
#include "PropDynamic.h"
#include "Vec3d.h"

class Camera : public PropDynamic
{
public:
	Camera(void);
	Camera(Vec3d position);
	void setupView();
	~Camera(void);
};


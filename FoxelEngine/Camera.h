#pragma once
#include <GL\glew.h>
#include "PropDynamic.h"
#include "Vec3d.h"
#include "Matrix4.h"
#include "World.h"

class Camera : public PropDynamic{
	Matrix4 viewMatrix;
public:
	Camera(void);
	Camera(Vec3d position);
	void setupView();
	~Camera(void);
};


#pragma once
#include <vector>
#include<GL\glew.h>
#include "Light.h"
class DirectLight{
private:
	std::vector<Light> lights;
	std::vector<int> id;
public:
	DirectLight(std::vector<int> id);

	
	float* generateDirectLightArray();

	std::vector<Light> getLight();
};


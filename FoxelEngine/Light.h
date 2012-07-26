#pragma once
#include "Color.h"
#include "Vec3.h"
struct Light{
	Color color;
	Vec3 normal,position;

	Light(Vec3 position, Vec3 normal, Color color){
		this->position = position;
		this->color = color;
		this->normal = normal;
	}

};


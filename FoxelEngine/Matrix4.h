#pragma once
#include <math.h>
#include <iostream>
#include "Vec3.h"
static const int M_SIZE = 4;
class Matrix4{

public:
	Matrix4(void);
	Matrix4(float* mat);
	~Matrix4(void);
	float matrix[M_SIZE*M_SIZE];

	static Matrix4 Identity();
	Matrix4 operator*(Matrix4 B);

	void scale(float x, float y, float z);
	void translate(float x,float y,float z);
	void rotate(float angle, float x, float y, float z);

	float* getMatrix();
	void printMatrix();
};


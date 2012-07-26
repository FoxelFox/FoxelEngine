#pragma once
#include <math.h>
#include <iostream>
#include "Vec3.h"
static const int M_SIZE = 4;
class Matrix4{

public:
	Matrix4(void);
	~Matrix4(void);
	float matrix[M_SIZE*M_SIZE];

	static Matrix4 Identity();

	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	static Matrix4 CreateFromAxisAngle(Vec3 axis, float angle);

	Matrix4 operator*(Matrix4 B);

	void scale(float x, float y, float z);
	void translate(float x,float y,float z);
	void translate(Vec3 vector);
	void rotate(float angle, float x, float y, float z);

	

	float* getMatrix();
	void printMatrix();
};


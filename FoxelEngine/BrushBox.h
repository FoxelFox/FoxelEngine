#pragma once
#include <GL\glew.h>
#include "DrawableGameComponent.h"
#include "Vec3.h"
#include "Screen.h"
#include "Color.h"

static GLfloat BoxV[] = {0.0f ,  0.0f ,  0.0f ,
				 128.0f,  0.0f ,  0.0f ,
				  0.0f , 128.0f,  0.0f ,
				  0.0f ,  0.0f , 128.0f,
				 128.0f, 128.0f, 128.0f,
				  0.0f , 128.0f, 128.0f,
				 128.0f,  0.0f , 128.0f,
				 128.0f, 128.0f,  0.0f ,};

static GLfloat BoxC[] = {1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f ,
				  1.0f ,  0.0f ,  0.0f };

static GLuint BoxI[] = {0,1, 0,2, 0,3, 4,5, 4,6, 4,7,
				 1,6, 2,5, 3,5, 2,7, 3,6, 1,7};

class BrushBox : public DrawableGameComponent{
private:
	Vec3 moved;
	Vec3 snapedPosition;
	Vec3 paintStart, paintStop;
	Vec3 size;
	bool painting;
	int paintID;
	void rebuildMesh();
	Color color;
public:
	BrushBox(void);
	~BrushBox(void);
	void draw();
	void startPaint();
	void stopPaint();
	void move(Vec3 value);
	void setSize(Vec3 size);
	void setPaintID(int id);
	void makeBlock();
	void setColor(Color color);
};


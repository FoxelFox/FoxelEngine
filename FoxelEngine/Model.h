#include <GL\glew.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <vector>


#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i)) // for VBO

struct GLVertex{
	GLfloat x,y,z;
	GLfloat a,b,c;
	GLfloat u,v;
};

struct Vertex{
	float x,y,z;
};

struct Normal{
	float a,b,c;
};

struct Textur{
	float u,v;
};

class Model{
private:
	static GLuint anzVertex, anzIndex;
	static GLVertex* vertices;
	static GLuint vao, *indices, vbos[2];
	static bool loaded;

	
public:
	Model();
	~Model();
	bool load(char* objfile);
	void draw();
};


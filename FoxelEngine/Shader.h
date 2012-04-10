#pragma once
#include <GL\glew.h>
#include <iostream>
#include <fstream>
class Shader{
private:
	GLuint programm, shaderID;
	GLint fileSize;
	char* fileSource;

	void loadFile(char* fileName);
	void getCompileError(GLint shader);
	void compile();
public:
	Shader(char* fileName);
	~Shader(void);
	
};


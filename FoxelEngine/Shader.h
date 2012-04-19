#pragma once
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <fstream>

namespace GLSL{
	enum ShaderTyp { VERTEX_SHADER = 0, FRAGMENT_SHADER = 1 };

	class Shader{
	private:
		bool imFine;
		std::string fileName;
		ShaderTyp shaderTyp;
		GLuint shaderObject;
		GLint fileSize;
		char* fileSource;

		void compile();
		void loadFile(std::string fileName);

	public:
		Shader(std::string fileName);
		~Shader(void);
		bool allRight();
		GLuint getShaderObject();

		static void printShaderLog(GLint object);
	};
};
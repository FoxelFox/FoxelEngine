#pragma once
#include <GL\glew.h>
#include <map>
#include "Shader.h"

#define ShaderProgram PM	// Programm Manager

namespace GLSL{
	enum ProgramTyp { PROGRAM_NULL = 0, PROGRAM_BASIC = 1, PROGRAM_FOXEL = 2, PROGRAM_MODEL = 3 , PROGRAM_POST = 4};

	class ShaderProgram{
	private:
		static ProgramTyp ActiveProgram;
		GLuint programObject;
		Shader* fragmentShader;
		Shader* vertexSchader;
		
	public:
		GLuint getProgram();
		ShaderProgram(ProgramTyp typ);
		~ShaderProgram(void);
		static void useProg(ProgramTyp typ);
		static GLint getUnifLoc(ProgramTyp typ, const GLchar *name);
		static GLint getActiveUnifLoc(const GLchar *name);
	};
	static std::map <int,ShaderProgram*> progMap;
};
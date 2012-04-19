#pragma once
#include <GL\glew.h>
#include <map>
#include "Shader.h"
namespace GLSL{
	enum ProgramTyp { PROGRAM_NULL = 0, PROGRAM_BASIC = 1 };

	class ShaderProgram{
	private:
		GLuint programObject;
		Shader* fragmentShader;
		Shader* vertexSchader;
	public:
		GLuint getProgram();
		ShaderProgram(ProgramTyp typ);
		~ShaderProgram(void);
		static void useProg(ProgramTyp typ);
		static GLint getUnifLoc(ProgramTyp typ, const GLchar *name);
	};
	static std::map <int,ShaderProgram*> progMap;
};
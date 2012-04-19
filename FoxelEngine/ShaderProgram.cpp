#include "ShaderProgram.h"

using namespace GLSL;
ShaderProgram::ShaderProgram(ProgramTyp typ){
	programObject = glCreateProgram();
	switch(typ){
		case PROGRAM_BASIC: fragmentShader = new Shader("Shader/Basic.frag");
		                    vertexSchader  = new Shader("Shader/Basic.vert");
							glBindAttribLocation(programObject,0, "in_Position");
							glBindAttribLocation(programObject,1, "in_Color");
							glBindAttribLocation(programObject,2, "in_Normal");
	}
	if(fragmentShader->allRight() && vertexSchader->allRight()){
		glAttachShader(programObject, fragmentShader->getShaderObject());
		glAttachShader(programObject, vertexSchader->getShaderObject());
		glLinkProgram(programObject);
	}
	// Get Linker Log
	Shader::printShaderLog(programObject); 
	delete fragmentShader, vertexSchader;
}


ShaderProgram::~ShaderProgram(void)
{
}

GLuint ShaderProgram::getProgram(){
	return programObject;
}

void ShaderProgram::useProg(ProgramTyp typ){
	if(progMap.find(typ) != progMap.end() || typ == PROGRAM_NULL){
		glUseProgram(progMap[typ]->getProgram());
	}else{
		progMap[typ] = new ShaderProgram(typ);
		useProg(typ);
	}
}

GLint ShaderProgram::getUnifLoc(ProgramTyp typ, const GLchar *name){
	return glGetUniformLocation(progMap[typ]->getProgram(), name);
}
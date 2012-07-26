#include "ShaderProgram.h"
#include <stdlib.h>

using namespace GLSL;
ProgramTyp ShaderProgram::ActiveProgram;
ShaderProgram::ShaderProgram(ProgramTyp typ){
	programObject = glCreateProgram();
	switch(typ){
		case PROGRAM_BASIC: fragmentShader = new Shader("Shader/Basic.frag");
		                    vertexSchader  = new Shader("Shader/Basic.vert");
							glBindAttribLocation(programObject,0, "in_Position");
							glBindAttribLocation(programObject,1, "in_Color");
							glBindAttribLocation(programObject,2, "in_Normal");
							break;
		case PROGRAM_FOXEL: fragmentShader = new Shader("Shader/Foxel.frag");
		                    vertexSchader  = new Shader("Shader/Foxel.vert");
							glBindAttribLocation(programObject,0, "in_Position");
							glBindAttribLocation(programObject,1, "in_Color");
							glBindAttribLocation(programObject,2, "in_Normal");
							break;
		case PROGRAM_MODEL: fragmentShader = new Shader("Shader/Model.frag");
							vertexSchader  = new Shader("Shader/Model.vert");
							glBindAttribLocation(programObject,0, "in_Position");
							glBindAttribLocation(programObject,1, "in_Color");
							glBindAttribLocation(programObject,2, "in_Normal");
							break;
		case PROGRAM_POST:  fragmentShader = new Shader("Shader/Post.frag");
						    vertexSchader  = new Shader("Shader/Post.vert");
						    break;
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
	if(progMap.find(typ) != progMap.end()){
		glUseProgram(progMap[typ]->getProgram());
		ActiveProgram = typ;
	}else if(typ == PROGRAM_NULL){
		glUseProgram(NULL);
	}else{
		progMap[typ] = new ShaderProgram(typ);
		useProg(typ);
	}
}

GLint ShaderProgram::getUnifLoc(ProgramTyp typ, const GLchar *name){
	if(progMap.find(typ) == progMap.end()){
		progMap[typ] = new ShaderProgram(typ);
	}
	return glGetUniformLocation(progMap[typ]->getProgram(), name);
}

GLint ShaderProgram::getActiveUnifLoc(const GLchar *name){
	return glGetUniformLocation(progMap[ActiveProgram]->getProgram(), name);
}
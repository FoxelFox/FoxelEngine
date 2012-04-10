#include "Shader.h"
using namespace std;

Shader::Shader(char* fileName){
	loadFile(fileName);
}


Shader::~Shader(void)
{
}

void Shader::loadFile(char* fileName){
	ifstream file (fileName, ios::in);
	if(file.is_open()){
		fileSize = (GLuint) file.tellg();
		fileSource = new char [fileSize];
		file.seekg(0,ios::beg);
		file.read(fileSource,fileSize);
		file.close();
	}else{
		cout << "Unable to open file " << fileName << endl;
	}
}

void Shader::compile(){
	GLuint shaderSource;
	shaderSource = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderSource,1,(const GLchar**)&fileSource,&fileSize);

	glCompileShader(shaderSource);

	GLint compiled;
	glGetShaderiv(shaderSource,GL_COMPILE_STATUS, &compiled); // get compile info
	if(!compiled){
		cout << "Shader not compiled." << endl;
		getCompileError(shaderSource);
	}

	programm = glCreateProgram();
	glBindAttribLocation(programm,0, "in_Position");

	glAttachShader(programm,shaderSource);
}

void getCompileError(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		cout << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}
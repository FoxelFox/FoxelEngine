#include "Shader.h"
using namespace std;
using namespace GLSL;
Shader::Shader(string fileName){
	imFine = true;
	fileSource = NULL;
	this->fileName = fileName;

	//get the right shader typ
	string fileTyp = fileName.substr(fileName.length()-4, fileName.length());
	if(fileTyp == "vert"){
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}else{
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}
	loadFile(fileName);
	if(imFine) compile();
}


Shader::~Shader(void){
	delete[] fileSource;
	//glDeleteShader(shaderObject);
}

void Shader::loadFile(string fileName){
	ifstream file (fileName, ios::in|ios::binary|ios::ate);
	if(file.is_open()){
		fileSize = (GLuint) file.tellg();
		fileSource = new char [fileSize];
		file.seekg(0,ios::beg);
		file.read(fileSource,fileSize);
		file.close();
	}else{
		cout << "Unable to open file " << fileName << endl;
		imFine = false;
	}
}

void Shader::compile(){
	const char* ss = fileSource;
	// load source code to GPU
	glShaderSource(shaderObject, 1, &ss , &fileSize);
	// compile source code on GPU
	glCompileShader(shaderObject);

	GLint compiled;
	// get compile info´s
	glGetShaderiv(shaderObject,GL_COMPILE_STATUS, &compiled);
	if(!compiled){
		cout << fileName << " not compiled!" << endl;
		printShaderLog(shaderObject);
		imFine = false;
	}
}

void Shader::printShaderLog(GLint object)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(object,infoLogLen, &charsWritten, infoLog);
		cout << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}

bool Shader::allRight(){
	return imFine;
}

GLuint Shader::getShaderObject(){
	return shaderObject;
}
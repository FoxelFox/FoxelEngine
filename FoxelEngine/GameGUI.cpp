#include "GameGUI.h"
#include "ShaderProgram.h"
#include "Screen.h"

using namespace GLSL;

GameGUI::GameGUI(void){
	debug = true;
	debugInformations = new TextField(Vec2(8,(float)Screen::getHeight()-22), Vec2(0,0));
	debugInformations->newLine("Polycount:    ");
	debugInformations->newLine("Chunk-Updates: ");
	debugInformations->newLine("GPU-Uploads:     ");
	debugInformations->newLine("Direct-Lights:   ");
	debugInformations->newLine("Bounce-Lights:  ");
}


GameGUI::~GameGUI(void){
	delete debugInformations;
}

void GameGUI::update(){

	debugInformations->setPosition(Vec2(8,(float)Screen::getHeight()-22));
	
	debugInformations->setContent(0,debug_PolycountInformation);
	debugInformations->setContent(1,debug_ChunkInformations);
	debugInformations->setContent(2,debug_GPU_Uploads);
	debugInformations->setContent(3,debug_DirectLights);
	debugInformations->setContent(4,debug_BounceLights);

}

void GameGUI::draw(){
	int cx = Screen::getWidth()/2;
	int cy = Screen::getHeight()/2;

	glColor3f(1.0f,0,0);
	glBegin(GL_LINES);
	{
		glVertex3f(cx-7,cy,-16);
		glVertex3f(cx-2,cy,-16);

		glVertex3f(cx+2,cy,-16);
		glVertex3f(cx+7,cy,-16);

		glVertex3f(cx,cy-7,-16);
		glVertex3f(cx,cy-2,-16);

		glVertex3f(cx,cy+2,-16);
		glVertex3f(cx,cy+7,-16);
	}
	glEnd();
	PM::useProg(PROGRAM_NULL);
	debugInformations->draw();
}

void GameGUI::setDebugChunkInformation(int value){
	std::stringstream ss;
	ss << "Chunk-Updates: " << value;
	debug_ChunkInformations = ss.str();
}

void GameGUI::setDebugPolycountInformation(long value){
	std::stringstream ss;
	ss << "Polycount:     " << value;
	debug_PolycountInformation = ss.str();
}

void GameGUI::setDebugGpuUploads(int value){
	std::stringstream ss;
	ss << "GPU-Uploads:    " << value;
	debug_GPU_Uploads = ss.str();
}

void GameGUI::setDebugDirectLightsCount(int value){
	std::stringstream ss;
	ss << "Direct-Lights:   " << value;
	debug_DirectLights = ss.str();
}

void GameGUI::setDebugBounceLightsCount(int value){
	std::stringstream ss;
	ss << "Bounce-Lights:  " << value;
	debug_BounceLights = ss.str();
}
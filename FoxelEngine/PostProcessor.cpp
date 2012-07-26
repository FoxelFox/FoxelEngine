#include "PostProcessor.h"
#include "Screen.h"
#include "Config.h"
#include "ShaderProgram.h"
#include "FoxelManager.h"

using namespace GLSL;

PostProcessor::PostProcessor(void)
{
}


PostProcessor::~PostProcessor(void)
{
}

bool PostProcessor::load(){
	glGenFramebuffers(1,&framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


	//-------------------------------------------------------------------------------------------------------------------
	// RGB - Texture
	glGenTextures(1,&renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::getWidth(), Screen::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	
	// Filtering for RGB - Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//-------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------------
	// RGB - Normal Texture
	glGenTextures(1,&normalTexture);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10, Screen::getWidth(), Screen::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	
	// Filtering for RGB - Normal Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//-------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------------
	// RGB - Position Texture
	glGenTextures(1,&positionTexture);
	glBindTexture(GL_TEXTURE_2D, positionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Screen::getWidth(), Screen::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	
	// Filtering for RGB - Position Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//-------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------------
	// Depth Texture
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,Screen::getWidth(), Screen::getHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, Screen::getWidth(), Screen::getHeight(), 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//-------------------------------------------------------------------------------------------------------------------


	// setting up
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, normalTexture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, positionTexture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	GLenum drawBuffers[3] = {GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, drawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		return false;
	}

	// Quad
	glGenBuffers(1,&quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	return true;
}

void PostProcessor::setupToDraw(){
	if(Screen::wasResized()){
		load();
	}

	generateBounceLightTexture();

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::draw(){

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		PM::useProg(PROGRAM_POST);

		// Activate and Bind Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTexture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, positionTexture);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthTexture);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_1D, bounceLightTexture);

		// Set our "renderedTexture" sampler to user Texture Unit 0
		glUniform1i(PM::getActiveUnifLoc("renderedTexture"), 0);
		glUniform1i(PM::getActiveUnifLoc("normalTexture"), 1);
		glUniform1i(PM::getActiveUnifLoc("positionTexture"), 2);
		glUniform1i(PM::getActiveUnifLoc("depthTexture"), 3);
		glUniform1i(PM::getActiveUnifLoc("bounceTexture"), 4);

		int displayMode;
		switch(Config::getDisplayMode()){
			case DisplayMode::DISPLAY_QUAD: displayMode = 1; break;
			case DisplayMode::DISPLAY_WITHOUT_RAD: displayMode = 2;  break;
			default: displayMode = 0;
		}
		glUniform1i(PM::getActiveUnifLoc("displayMode"), displayMode);
		glUniform1i(PM::getActiveUnifLoc("bounceLightCount"), FoxelManager::getNumberOfBounceLights());
		glUniform2f(PM::getActiveUnifLoc("screen"),(float)Screen::getWidth(), (float) Screen::getHeight());

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // From index 0 to 3 -> 1 triangle

		glDisableVertexAttribArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
}

void PostProcessor::generateBounceLightTexture(){
	//glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	//glClampColor(GL_CLAMP_VERTEX_COLOR, GL_FALSE);
	//glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);


	glGenTextures(1,&bounceLightTexture);
	glBindTexture(GL_TEXTURE_1D, bounceLightTexture);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB16F, FoxelManager::getNumberOfBounceLights() * 3,0,GL_RGB,GL_FLOAT, FoxelManager::getBounceLightArray());
	
	// Filtering for RGB - Texture
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
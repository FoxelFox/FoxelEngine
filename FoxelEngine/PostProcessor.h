#pragma once
#include <GL\glew.h>

static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
};


class PostProcessor{
private:
	GLuint framebuffer;
	GLuint renderedTexture;
	GLuint positionTexture;
	GLuint normalTexture;
	GLuint depthTexture;
	GLuint depthrenderbuffer;

	GLuint quad_VertexArrayID;
	GLuint quad_vertexbuffer;

	GLuint bounceLightTexture;
	void generateBounceLightTexture();

public:
	PostProcessor(void);
	~PostProcessor(void);
	void setupToDraw();
	void draw();
	bool load();
};


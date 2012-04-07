#include "TextField.h"


TextField::TextField(Vec2 position, Vec2 size, std::string content) : Entity_2D(position, size){
	linesOfContent.push_back(content);
	textColor[0] = 1; textColor[1] = 1; textColor[2] = 1;
	withBox = true;
	boxPadding = 4;
}

TextField::TextField(Vec2 position, Vec2 size){
	textColor[0] = 1; textColor[1] = 1; textColor[2] = 1;
	withBox = true;
	boxPadding = 4;
}


void TextField::setContent(int line, std::string newContent){
	linesOfContent.erase(linesOfContent.begin()+line);
	linesOfContent.insert(linesOfContent.begin()+line, newContent);
}

void TextField::newLine(std::string newContent){
	linesOfContent.push_back(newContent);
}


void TextField::draw(){

	glColor3f(0.1f,0.1f,0.1f);
	if(withBox){
		glBegin(GL_QUADS);
		 glVertex2d(position.x		    - boxPadding, position.y          - boxPadding);
		 glVertex2d(position.x + size.x + boxPadding, position.y          - boxPadding);
		 glVertex2d(position.x + size.x + boxPadding, position.y + size.y + boxPadding);
		 glVertex2d(position.x		    - boxPadding, position.y + size.y + boxPadding);
		glEnd();
	}

	glColor3f(textColor[0], textColor[1], textColor[2]);
	glTranslated(position.x, position.y, 0);
	
	
	for(unsigned int i = 0; i < linesOfContent.size(); i++){
		glRasterPos2f(0,(float) -20*i);
		linesOfContent[i].draw();
	}

	glTranslated(-position.x, -position.y, 0);
}

Vec2 TextField::getPosition(){
	return position;
}

void TextField::setTextColor(float r, float g, float b){
	textColor[0] = r;
	textColor[1] = g;
	textColor[2] = b;
}

TextField::~TextField(void){

}

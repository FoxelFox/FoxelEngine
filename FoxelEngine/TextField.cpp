#include "TextField.h"


TextField::TextField(Vec2 position, Vec2 size, std::string content) : Entity_2D(position, size){
	linesOfContent.push_back(content);
	textColor[0] = 1; textColor[1] = 1; textColor[2] = 1;
	withBox = true;
	bigText = true;
	boxPadding = 4;
}

TextField::TextField(Vec2 position, Vec2 size){
	textColor[0] = 1; textColor[1] = 1; textColor[2] = 1;
	withBox = true;
	bigText = true;
	boxPadding = 4;
}


void TextField::setContent(int line, std::string newContent){
	linesOfContent[line] = newContent;
	linesOfContent[line].setBigText(bigText);
}

void TextField::newLine(std::string newContent){
	linesOfContent.push_back(newContent);
}


void TextField::draw(){
	glEnable(GL_BLEND);
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
	glTranslated(position.x, position.y, 1);
	
	glDisable(GL_BLEND);
	for(unsigned int i = 0; i < linesOfContent.size(); i++){
		glRasterPos2f(0,(float) -20*i);
		linesOfContent[i].draw();
	}

	glTranslated(-position.x, -position.y, -1);
	
}

Vec2 TextField::getPosition(){
	return position;
}

void TextField::setWithBox(bool boolean){
	withBox = boolean;
}

void TextField::setTextColor(float r, float g, float b){
	textColor[0] = r;
	textColor[1] = g;
	textColor[2] = b;
}

void TextField::setBigText(bool boolean){
	bigText = boolean;
	for(unsigned int i = 0; i < linesOfContent.size(); i++){
		linesOfContent[i].setBigText(boolean);
	}
}

TextField::~TextField(void){

}

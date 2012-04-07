#include "ToolBox.h"


ToolBox::ToolBox(Vec2 position, Vec2 size) : GameMenu(position, size){
    selectOptions.push_back(TextButton(Vec2(16,GL_Screen::getHeight()-28),Vec2(96,14),"Brush"));
}


ToolBox::~ToolBox(void){

}

void ToolBox::draw(){
    glColor3f(0.5f,0.1f,0.1f);
	glBegin(GL_QUADS);
	glVertex2f(position.x, position.y);
	glVertex2f(size.x	  , position.y);
	glVertex2f(size.x	  , size.y	  );
	glVertex2f(position.x, size.y);
	glEnd();
    GameMenu::draw();
}
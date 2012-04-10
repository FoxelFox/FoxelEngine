#include "ToolBox.h"

using namespace MapEditor;
ToolBox::ToolBox(Vec2 position, Vec2 size) : GameMenu(position, size){ 
    int y = 28;     
    selectOptions.push_back(TextButton(Vec2(16,(float)Screen::getHeight()-y),Vec2(96,14),"Brush"));  y += 28;
    selectOptions.push_back(TextButton(Vec2(16,(float)Screen::getHeight()-y),Vec2(96,14),"Entity")); y += 28;

}


ToolBox::~ToolBox(void){

}

void ToolBox::draw(){
	glBegin(GL_QUADS);
	glColor3f(0.0f,0.0f,0.0f);  glVertex2f(position.x, position.y);
	                            glVertex2f(size.x	  , position.y);
	glColor3f(0.5f,0.1f,0.1f);  glVertex2f(size.x	  , size.y	  );
	                            glVertex2f(position.x, size.y);
	                            glEnd();
    GameMenu::draw();
}

void ToolBox::resize(){
    size.y = (float)Screen::getHeight();
    int y = 28;
    for(int i = 0; i < selectOptions.size(); i++){ 
        selectOptions[i].setPosition(Vec2(16,(float)Screen::getHeight() - y));
        y += 28;
    }
}
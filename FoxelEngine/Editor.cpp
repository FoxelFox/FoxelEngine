#include "Editor.h"
#include <SDL\SDL.h>

using namespace MapEditor;

Editor::Editor(void) : GameMenu(){
	b = 4;
	toolBox = new ToolBox(Vec2(0,0),Vec2(128,(float)GL_Screen::getHeight()));
	Vec2 viewSize;
	viewSize.x = (float)(GL_Screen::getWidth()  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(GL_Screen::getHeight() / 2);
	views.push_back(new View(VIEW_RIGHT	, Vec2(  0 + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_TOP	, Vec2(viewSize.x + toolBox->getSize().x,viewSize.y), viewSize));
	views.push_back(new View(VIEW_FRONT , Vec2(viewSize.x + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_3D	, Vec2(  0 + toolBox->getSize().x, viewSize.y), viewSize));
					
}

Editor::~Editor(void){
}

void Editor::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GL_Screen::load2DView();
    toolBox->draw();
    glDisable(GL_BLEND);
	for(int i = 0; i < 4; i++){
		views[i]->setUp();
		views[i]->draw();
	}
    glEnable(GL_BLEND);
}

void Editor::catchMousePosition(Vec2 pos){

}

void Editor::catchMouseClick(Vec2 pos){

}

void Editor::resize(){
   	Vec2 viewSize;
	viewSize.x = (float)(GL_Screen::getWidth()  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(GL_Screen::getHeight() / 2);
    
}
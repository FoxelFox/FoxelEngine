#include "Editor.h"
#include <SDL\SDL.h>

using namespace MapEditor;

Editor::Editor(void) : GameMenu(){
	b = 4;
	screenWidth = 1280;
	screenHeight = 720;
	toolBox = new ToolBox(Vec2(0,0),Vec2(128,(float)screenHeight));
	Vec2 viewSize;
	viewSize.x = (float)(screenWidth  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(screenHeight / 2);
	views.push_back(new View(VIEW_RIGHT	, Vec2(  0 + b+toolBox->getSize().x,    0+b  ), viewSize));
	views.push_back(new View(VIEW_TOP	, Vec2(viewSize.x +b*2+toolBox->getSize().x,viewSize.y+b*2), viewSize));
	views.push_back(new View(VIEW_FRONT , Vec2(viewSize.x+b*2+toolBox->getSize().x,  0+b  ), viewSize));
	views.push_back(new View(VIEW_3D	, Vec2(  0 + b+toolBox->getSize().x,  viewSize.y+b*2), viewSize));
					
	glDisable(GL_BLEND);
}

Editor::~Editor(void){
}

void Editor::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int i = 0; i < 4; i++){
		views[i]->setUp();
		views[i]->draw();
	}
}

void Editor::catchMousePosition(Vec2 pos){

}

void Editor::catchMouseClick(Vec2 pos){

}
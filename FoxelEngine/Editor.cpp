#include <SDL\SDL.h>
#include "Editor.h"

using namespace MapEditor;
using namespace GLSL;

int Editor::gridDeep = 8;

Editor::Editor(void) : GameMenu(){
	playMode = false;
	controler = new Controler();
	toolBox = new ToolBox(Vec2(0,0),Vec2(128,(float)Screen::getHeight()));
	brush = new BrushBox();
	center = new Axes();

	center->load();

	Vec2 viewSize;
	viewSize.x = (float)(Screen::getWidth()  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(Screen::getHeight() / 2);
	views.push_back(new View(VIEW_RIGHT	, Vec2(  0 + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_TOP	, Vec2(viewSize.x + toolBox->getSize().x,viewSize.y), viewSize));
	views.push_back(new View(VIEW_FRONT , Vec2(viewSize.x + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_3D	, Vec2(  0 + toolBox->getSize().x, viewSize.y), viewSize));

	colorPanel = new ColorPanel(Vec2(Screen::getWidth() - 128 ,Screen::getHeight()-220), Vec2(128,220));
	brush->setColor(colorPanel->getColor());
}

Editor::~Editor(void){
}

void Editor::draw(){
	Screen::load2DView();
	toolBox->draw();
	colorPanel->draw();
	PM::useProg(PROGRAM_FOXEL);
	for(int i = 0; i < 4; i++){
		views[i]->setUp();
		views[i]->draw();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		FoxelManager::render();
		PM::useProg(PROGRAM_BASIC);
		brush->draw();
		center->render();
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
	}
	PM::useProg(PROGRAM_NULL);
}

void Editor::update(float* time){
	Map::update();
	toolBox->update();
	bool mouseIsMoving = Screen::getMouseMotion().x != 0 || Screen::getMouseMotion().y != 0;
	
	if(controler->Grab || controler->midleMouseButton){
		// stay on active view
	}else{
		activeView = catchActiveView();
	}
	if(controler->Tab){
		if(playMode == true){
			playMode = false;
			Screen::showMouse();
		}else{
			playMode = true;
			Screen::hideMouse();
		}
		controler->Tab = false;
	}
	for(int i = 0; i < views.size(); i++){
		views[i]->update(time);
	}

	// on 3D view
	if(playMode && mouseIsMoving){
		views[3]->getPlayer()->catchMouseMotion(-Screen::getMouseMotion().x, Screen::getMouseMotion().y);
	}

	if(controler->Grab){
		Screen::hideMouse();
		if(controler->leftMouseButton){
			brush->startPaint();
			brush->setPaintID(1);
		}else if(controler->rightMouseButton){
			brush->startPaint();
			brush->setPaintID(0);
		}else{
			brush->stopPaint();
		}
		// Move Brush
		if(!controler->midleMouseButton && mouseIsMoving && activeView != NULL){
			switch(activeView->getViewMode()){
			case VIEW_TOP:    brush->move(Vec3(-Screen::getMouseMotion().x / activeView->zoom,-Screen::getMouseMotion().y / activeView->zoom,0.0f)); break;
			case VIEW_FRONT:  brush->move(Vec3(-Screen::getMouseMotion().x / activeView->zoom,0.0f,-Screen::getMouseMotion().y / activeView->zoom)); break;
			case VIEW_RIGHT:  brush->move(Vec3(0.0f,Screen::getMouseMotion().x / activeView->zoom,-Screen::getMouseMotion().y / activeView->zoom)); break;
			}
		}

	}

	// color panel
	if(mouseIsMoving && controler->leftMouseButton && colorPanel->mouseIntersect()){
		colorPanel->mouseInteraction();
		brush->setColor(colorPanel->getColor());
	}

	// Move View if midleMouse Button is pressed
	if(controler->midleMouseButton && mouseIsMoving && activeView != NULL){
		activeView->moveViewPosition(Vec3(Screen::getMouseMotion().x, Screen::getMouseMotion().y,0));
	}

	if(controler->wheelState != 0 && activeView != NULL){
		activeView->addZoomValue((float)controler->wheelState);
		controler->wheelState = 0;
	}
}

void Editor::catchMouseClick(Vec2 pos){

}

View* Editor::catchActiveView(){
	for(int i = 0; i < views.size(); i++){
		if((Screen::getMousePosition().x > views[i]->getPosition().x
		 && Screen::getMousePosition().x < views[i]->getPosition().x + views[i]->getSize().x)
		 && Screen::getMousePosition().y > views[i]->getPosition().y
		 && Screen::getMousePosition().y < views[i]->getPosition().y + views[i]->getSize().y){
			return views[i];
		}
	}
	return NULL;
}

void Editor::resize(){
	toolBox->resize();

	Vec2 viewSize;
	viewSize.x = (float)(Screen::getWidth()  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(Screen::getHeight() / 2);
	views[0]->setPosition(Vec2(0 + toolBox->getSize().x, 0));
	views[1]->setPosition(Vec2(viewSize.x + toolBox->getSize().x,viewSize.y));
	views[2]->setPosition(Vec2(viewSize.x + toolBox->getSize().x, 0 ));
	views[3]->setPosition(Vec2(  0 + toolBox->getSize().x, viewSize.y));

	for(int i = 0; i < views.size(); i++){
		views[i]->setSize(viewSize);
	}

	colorPanel->resize(Vec2(Screen::getWidth() - 128 ,Screen::getHeight()-220));
}

void Editor::catchKeyDown(SDLKey sym){
	controler->catchKeyDown(sym);
	if(playMode) views[3]->getPlayer()->catchKeyDown(sym);
}

void Editor::catchKeyUp(SDLKey sym){
	controler->catchKeyUp(sym);
	views[3]->getPlayer()->catchKeyUp(sym);
}

int Editor::getGridDeep(){
	return gridDeep;
}

Controler* Editor::getControler(){
	return controler;
}
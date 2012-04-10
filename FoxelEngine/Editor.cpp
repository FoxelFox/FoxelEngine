#include "Editor.h"
#include "GlobalLight.h"
#include <SDL\SDL.h>

using namespace MapEditor;

Editor::Editor(void) : GameMenu(){
	playMode = false;
	controler = new Controler();
	toolBox = new ToolBox(Vec2(0,0),Vec2(128,(float)Screen::getHeight()));

	Vec2 viewSize;
	viewSize.x = (float)(Screen::getWidth()  / 2) - toolBox->getSize().x;
	viewSize.y = (float)(Screen::getHeight() / 2);
	views.push_back(new View(VIEW_RIGHT	, Vec2(  0 + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_TOP	, Vec2(viewSize.x + toolBox->getSize().x,viewSize.y), viewSize));
	views.push_back(new View(VIEW_FRONT , Vec2(viewSize.x + toolBox->getSize().x, 0 ), viewSize));
	views.push_back(new View(VIEW_3D	, Vec2(  0 + toolBox->getSize().x, viewSize.y), viewSize));

}

Editor::~Editor(void){
}

void Editor::draw(){
	Screen::load2DView();
	toolBox->draw();
	for(int i = 0; i < 4; i++){
		views[i]->setUp();
		glDisable(GL_BLEND);
		GlobalLight::turnOn();
		views[i]->draw();
		GlobalLight::turnOff();
		glEnable(GL_BLEND);
	}
}

void Editor::update(float* time){
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

	if(playMode && (Screen::getMouseMotion().x != 0 || Screen::getMouseMotion().y != 0)){
		views[3]->getPlayer()->catchMouseMotion(-Screen::getMouseMotion().x, Screen::getMouseMotion().y);
	}

	// Move View if midleMouse Button is pressed
	if(controler->midleMouseButton && (Screen::getMouseMotion().x != 0 || Screen::getMouseMotion().y != 0)){
		try{
			catchActiveView()->moveViewPosition(Vec3(Screen::getMouseMotion().x, Screen::getMouseMotion().y,0));
		}catch(int noView){
			noView = 0;// Mouse isnt on a view
		}
	}

	if(controler->wheelState != 0){
		try{
			catchActiveView()->addZoomValue((float)controler->wheelState);
		}catch(int noView){
			noView = 0;// Mouse isnt on a view
		}
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
	throw NULL;
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
}
void Editor::catchKeyDown(SDLKey sym){
	controler->catchKeyDown(sym);
	if(playMode) views[3]->getPlayer()->catchKeyDown(sym);
}

void Editor::catchKeyUp(SDLKey sym){
	controler->catchKeyUp(sym);
	views[3]->getPlayer()->catchKeyUp(sym);
}

Controler* Editor::getControler(){
	return controler;
}
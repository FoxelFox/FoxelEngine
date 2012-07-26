#include "GameMenu.h"


GameMenu::GameMenu(Vec2 position, Vec2 size) : Entity_2D(position, size){

}

GameMenu::GameMenu(){}

GameMenu::~GameMenu(void){
}

void GameMenu::update(){
	catchMousePosition(Screen::getMousePosition());
	if(Screen::isKlickLeft()) catchMouseClick(Screen::getMousePosition());
}

void GameMenu::draw(){
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		selectOptions[i].draw();
	}
}

void GameMenu::catchMousePosition(Vec2 mpos){
	//mpos.y += Screen::getHeight() - 2 *mpos.y;
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		if(selectOptions[i].intersect(mpos)){
			selectOptions[i].setTextColor(1.0f,0.0f,0.0f);
		}else{
			selectOptions[i].setTextColor(1.0f,1.0f,1.0f);
		}
	}
}

void GameMenu::catchMouseClick(Vec2 mpos){
	//mpos.y += Screen::getHeight() - 2 *mpos.y;
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		if(selectOptions[i].intersect(mpos)){
			selectOptions[i].press();		
		}else{
			selectOptions[i].release();
		}
	}
	createEvents();
}

void GameMenu::createEvents(){}
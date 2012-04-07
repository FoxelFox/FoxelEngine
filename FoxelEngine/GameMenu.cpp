#include "GameMenu.h"


GameMenu::GameMenu(Vec2 position, Vec2 size) : Entity_2D(position, size){

}

GameMenu::GameMenu(){}

GameMenu::~GameMenu(void){
}

void GameMenu::draw(){
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		selectOptions[i].draw();
	}
}

void GameMenu::catchMousePosition(Vec2 mpos){
	mpos.y += screenHeight - 2 *mpos.y;
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		if(mpos.y > selectOptions[i].getPosition().y-4 && mpos.y < selectOptions[i].getPosition().y+20){
			selectOptions[i].setTextColor(1.0f,0.0f,0.0f);
		}else{
			selectOptions[i].setTextColor(1.0f,1.0f,1.0f);
		}
	}
}

void GameMenu::catchMouseClick(Vec2 mpos){
	mpos.y += screenHeight - 2 *mpos.y;
	for(unsigned int i = 0; i < selectOptions.size(); i++){
		if(mpos.y > selectOptions[i].getPosition().y-4 && mpos.y < selectOptions[i].getPosition().y+20){
			selectOptions[i].press();		
		}else{
			selectOptions[i].release();
		}
	}
	createEvents();
}

void GameMenu::createEvents(){}

void GameMenu::setScreenSize(int w, int h){
	screenWidth = w;
	screenHeight = h;
}
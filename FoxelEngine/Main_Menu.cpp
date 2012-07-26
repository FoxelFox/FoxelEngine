#include "Main_Menu.h"
#include <iostream>

Main_Menu::Main_Menu(void){
	position.x = 60-8;
	position.y = 60-8;
	size.x = 256 -60+8;
	size.y = 256+26;
	selectOptions.push_back(TextButton(Vec2(64,256),Vec2(128,14),"Play"));
	selectOptions.push_back(TextButton(Vec2(64,192),Vec2(128,14),"Level Editor"));
	selectOptions.push_back(TextButton(Vec2(64,128),Vec2(128,14),"Options"));
	selectOptions.push_back(TextButton(Vec2(64,64),Vec2(128,14),"Exit"));
}

Main_Menu::~Main_Menu(void){

}

void Main_Menu::draw(){

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, Screen::getWidth(), 0, Screen::getHeight(), -128, 128);
   
	glColor3f(0.1f,0.1f,0.1f);
	glBegin(GL_QUADS);
	glVertex2f(position.x, position.y);
	glVertex2f(size.x	  , position.y);
	glVertex2f(size.x	  , size.y	  );
	glVertex2f(position.x, size.y);
	glEnd();

	glBegin(GL_QUADS);
	 glVertex2f(position.x		  , 282	  );
	 glVertex2f(position.x-16	  , 264	  );
	 glVertex2f(position.x-16	  , position.y+16);
	 glVertex2f(position.x, position.y);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(size.x, size.y-112	  );
	glVertex2f(size.x+16	  , size.y-48-48	  );
	glVertex2f(size.x+16	  , size.y-16);
	glVertex2f(size.x, size.y);
	glEnd();

	GameMenu::draw();
}

void Main_Menu::createEvents(){
	if(selectOptions[0].isPressed()){
		new Event::BasicEvent(Event::PLAYMODE);
		selectOptions[0].release();
	}
	if(selectOptions[1].isPressed()){
		new Event::BasicEvent(Event::EDITMODE);
	}
	if(selectOptions[3].isPressed()){
		new Event::BasicEvent(Event::EXIT);
		selectOptions[3].release();
	}
}
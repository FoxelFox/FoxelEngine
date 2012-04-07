#include "BitMapText.h"


BitmapText::BitmapText(std::string newText){
	text = newText;
}

void BitmapText::setText(std::string newText){
	text = newText;
}


void BitmapText::draw(){
	for(int i = 0; i < text.length(); i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text.at(i));
	}
}


BitmapText::~BitmapText(void){

}
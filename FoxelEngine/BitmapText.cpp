#include "BitMapText.h"


BitmapText::BitmapText(std::string newText){
	text = newText;
	bigText = true;
}

void BitmapText::setText(std::string newText){
	text = newText;
		bigText = true;
}


void BitmapText::draw(){
	for(int i = 0; i < text.length(); i++){
		if(bigText){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
		}else{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,text[i]);
		}
		
	}
}

void BitmapText::setBigText(bool boolean){
	bigText = boolean;
}

BitmapText::~BitmapText(void){

}
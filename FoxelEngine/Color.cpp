#include "Color.h"

Color::Color(void){
	RGBA[0] = RGBA[1] = RGBA[2] = 200;
	RGBA[3] = 255;
}

Color::Color(unsigned char R, unsigned char G, unsigned char B){
	RGBA[0] = R;
	RGBA[1] = G;
	RGBA[2] = B;
	RGBA[3] = 255;
}

Color::Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A){
	RGBA[0] = R;
	RGBA[1] = G;
	RGBA[2] = B;
	RGBA[3] = A;
}

unsigned char* Color::getColorArray(){
	return RGBA;
}

unsigned char Color::getRed(){
	return RGBA[0];
}

unsigned char Color::getGreen(){
	return RGBA[1];
}

unsigned char Color::getBlue(){
	return RGBA[2];
}

unsigned char Color::getAlpha(){
	return RGBA[3];
}

void Color::setColor(unsigned char r, unsigned char g, unsigned char b){
	RGBA[0] = r;
	RGBA[1] = g;
	RGBA[2] = b;
}

void Color::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	RGBA[0] = r;
	RGBA[1] = g;
	RGBA[2] = b;
	RGBA[3] = a;
}

void Color::setRed(unsigned char r){
	RGBA[0] = r;
}

void Color::setGreen(unsigned char g){
	RGBA[1] = g;
}

void Color::setBlue(unsigned char b){
	RGBA[2] = b;
}

void Color::setAlpha(unsigned char a){
	RGBA[3] = a;
}

unsigned char Color::getMaximum(){
	unsigned char max;
	if(RGBA[0] > RGBA[1]){
		max = RGBA[0];
	}else{
		max = RGBA[1];
	}
	if(max < RGBA[2]){
		max = RGBA[2];
	}
	return max;
}

short Color::getLuminate(){
	return RGBA[0] + RGBA[1] + RGBA[2];
}
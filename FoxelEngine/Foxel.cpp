#include "foxel.h"


Foxel::Foxel()
{
	color[0] = 64 , color[1] = 64 , color[2] = 64;
	visiblity = 63;
	id = 0;
}
Foxel::Foxel(char idFoxel, char vis){
	color[0] = 64 , color[1] = 64 , color[2] = 64;
	visiblity = vis;
	id = idFoxel;
	test = true;
}


Foxel::~Foxel()
{
}

void Foxel::setColor(GLushort r, GLushort g, GLushort b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

// Setzt Das jeweilige bit
void Foxel::setVisiblity(char setBit){
	if(setBit > 0){
		visiblity |= setBit;
	}else{
		visiblity &= setBit;
	}
}

char Foxel::getVisiblity(){
	return visiblity;
}

void Foxel::setId(char setterID){
	id = setterID;
}

char Foxel::getId(){
	return id;
}

GLushort* Foxel::getColor(){
	return color;
}

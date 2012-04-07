#include "Entity_2D.h"


Entity_2D::Entity_2D(Vec2 position, Vec2 size){
	this->position = position;
	this->size = size;
}

Entity_2D::Entity_2D(){}

Entity_2D::~Entity_2D(void){
}

void Entity_2D::move(Vec2 value){
	this->position += value;
}

void Entity_2D::setPosition(Vec2 position){
	this->position = position;
}

void Entity_2D::setSize(Vec2 size){
	this->size = size;
}


Vec2 Entity_2D::getPosition(){
	return position;
}

Vec2 Entity_2D::getSize(){
	return size;
}
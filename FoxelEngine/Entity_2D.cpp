#include "Entity_2D.h"
#include "Screen.h"

Entity_2D::Entity_2D(Vec2 position, Vec2 size){
	this->position = position;
	this->size = size;
	backColor.setColor(32,32,32,255);
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

void Entity_2D::drawBackground(){
	glColor4ub(backColor.getRed(),backColor.getGreen(),backColor.getBlue(),backColor.getAlpha());
	glBegin(GL_QUADS);
	glVertex3f(position.x, position.y, -64.0f);
	glVertex3f(position.x + size.x, position.y, -64.0f);
	glVertex3f(position.x + size.x, position.y + size.y, -64.0f);
	glVertex3f(position.x, position.y + size.y, -64.0f);



	glEnd();
}

bool Entity_2D::mouseIntersect(){
	Vec2 m = Screen::getMousePosition();
	return (m.x > position.x) && (m.x < (position.x + size.x))
		&& (m.y > position.y) && (m.y < (position.y + size.y));
}

void Entity_2D::setBackColor(Color color){
	backColor = color;
}

Vec2 Entity_2D::getPosition(){
	return position;
}

Vec2 Entity_2D::getSize(){
	return size;
}
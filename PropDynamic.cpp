#include "PropDynamic.h"


PropDynamic::PropDynamic(void) : GameComponent(){
	friction = 0.005f;
}

PropDynamic::PropDynamic(Vec3d position){
	friction = 0.005f;
	this->position = position;
}

void PropDynamic::update(float* time){
	velocity -= velocity * (friction / 2*(*time));
	position += velocity **time;
}

//-------------------------------------------------------------------------
// Setter Methods
//-------------------------------------------------------------------------
void PropDynamic::setFriction(float friction){
	PropDynamic::friction = friction;
}
void PropDynamic::setRotation(Vec3d rotation){
	this->rotation = rotation;
}
void PropDynamic::setPosition(Vec3d position){
	this->position = position;
}

PropDynamic::~PropDynamic(void)
{
}

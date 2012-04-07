#include "Camera.h"


Camera::Camera() : PropDynamic(){
}

Camera::Camera(Vec3d position)
	: PropDynamic(position){
}
void Camera::setupView(){
	glLoadIdentity();
	glRotatef((float)rotation.x, 1, 0, 0);
	glRotatef((float)rotation.z, 0, 0, 1);
	glTranslated(position.x,position.y,position.z);
}

Camera::~Camera(void){
}

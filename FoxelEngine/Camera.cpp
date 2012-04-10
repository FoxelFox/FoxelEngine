#include "Camera.h"


Camera::Camera() : PropDynamic(){
}

Camera::Camera(Vec3d position)
	: PropDynamic(position){
}
void Camera::setupView(){
	glLoadIdentity();
	glRotated(rotation.x, 1, 0, 0);
	glRotated(rotation.z, 0, 0, 1);
	glTranslated(position.x,position.y,position.z);
}

Camera::~Camera(void){
}

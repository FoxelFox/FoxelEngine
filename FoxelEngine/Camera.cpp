#include "Camera.h"
using namespace GLSL;

Camera::Camera() : PropDynamic(){
}

Camera::Camera(Vec3d position)
	: PropDynamic(position){
}
void Camera::setupView(){
	Screen::ViewMatrix = Matrix4::Identity();
	Screen::ViewMatrix.rotate(rotation.x, 1, 0, 0);
	Screen::ViewMatrix.rotate(rotation.z, 0, 0, 1);
	Screen::ViewMatrix.translate(position.x,position.y,position.z);
	glUniform3f(PM::getActiveUnifLoc("player_position"),-position.x,-position.y,-position.z);
}

Camera::~Camera(void){
}


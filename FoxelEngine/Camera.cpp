#include "Camera.h"
using namespace GLSL;

Camera::Camera() : PropDynamic(){
}

Camera::Camera(Vec3d position)
	: PropDynamic(position){
}
void Camera::setupView(){
	Screen::ViewMatrix = Matrix4::Identity();
	Screen::ViewMatrix.rotate((float)rotation.x, 1.0f, 0.0f, 0.0f);
	Screen::ViewMatrix.rotate((float)rotation.z, 0.0f, 0.0f, 1.0f);
	Screen::ViewMatrix.translate((float)position.x,(float)position.y,(float)position.z);
	PM::useProg(PROGRAM_MODEL);
	glUniform3f(PM::getActiveUnifLoc("player_position"),(float)-position.x,(float)-position.y,(float)-position.z);
	PM::useProg(PROGRAM_FOXEL);
	glUniform3f(PM::getActiveUnifLoc("player_position"),(float)-position.x,(float)-position.y,(float)-position.z);
}

Camera::~Camera(void){
}


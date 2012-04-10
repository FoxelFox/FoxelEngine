#include "GlobalLight.h"

GlobalLight::GlobalLight(void){
}


GlobalLight::~GlobalLight(void)
{
}

void GlobalLight::load(){
	ambientLight = new GLfloat[4];
	diffuseLight = new GLfloat[4];
	specularLight = new GLfloat[4];
	mat_specular = new GLfloat[4];
	mat_shininess = new GLfloat[4];

	ambientLight[0] = 0.25f;ambientLight[0] = 0.2f; ambientLight[0] = 0.2f; ambientLight[0] = 0.1f;
	diffuseLight[0] = 0.8f;diffuseLight[0] = 0.8f; diffuseLight[0] = 0.8f; diffuseLight[0] = 1.0f;
	specularLight[0] = 0.5f;specularLight[0] = 0.5f; specularLight[0] = 0.5f; specularLight[0] = 1.0f;
	mat_specular[0] = 0.4f;mat_specular[0] = 0.4f; mat_specular[0] = 0.4f; mat_specular[0] = 0.1f;
	mat_shininess[0] = 1.0f;


	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
}

void GlobalLight::lightAt(Vec3 position){
	GLfloat lightPosition[] = { position.x, position.y, position.z, 0.1f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GlobalLight::turnOff(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void GlobalLight::turnOn(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
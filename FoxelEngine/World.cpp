#include "World.h"

using namespace GLSL;

World::World(void){
	center = new Axes();
}

bool World::load(){
	Vec3d* test = new Vec3d(2.0,2.0,2.0);
	new Event::setFoxel(test,1);
	center->load();
	return true;
}

void World::render(){
	ShaderProgram::useProg(PROGRAM_BASIC);
	glUniform4f(ShaderProgram::getUnifLoc(PROGRAM_BASIC, "test"), 0.0, 1.0, 0.0, 1.0);
	glUniformMatrix4fv(ShaderProgram::getUnifLoc(PROGRAM_BASIC, "projMatrix"), 1, GL_FALSE, Screen::getProjectionMatrix());
	glUniformMatrix4fv(ShaderProgram::getUnifLoc(PROGRAM_BASIC, "viewMatrix"), 1, GL_FALSE, Screen::ViewMatrix.getMatrix());

	FoxelManager::render();
	center->render();
	glutSolidRhombicDodecahedron();
	glUseProgram(NULL);
}

World::~World(void){
	FoxelManager::deleteAll();
}

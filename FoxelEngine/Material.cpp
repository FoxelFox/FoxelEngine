#include "Material.h"
using namespace GLSL;

Material::Material(ProgramTyp materialTyp){
	this->materialTyp = materialTyp;
}

Material::Material(ProgramTyp materialTyp, Color defuse, Color specular){
	this->materialTyp = materialTyp;
	this->defuse = defuse;
	this->specular = specular;
}

Material::~Material(void)
{
}

void Material::use(){
	PM::useProg(materialTyp);
}

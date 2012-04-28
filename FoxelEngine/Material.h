#pragma once
#include "Color.h"
#include "ShaderProgram.h"
namespace GLSL{
	class Material{
		Color defuse,specular;
		ProgramTyp materialTyp;
	public:
		Material(ProgramTyp materialTyp);
		Material(ProgramTyp materialTyp, Color defuse, Color specular);
		~Material(void);
		void use();
	};
};


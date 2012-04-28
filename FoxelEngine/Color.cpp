#include "Color.h"
using namespace GLSL;
Color::Color(void){
	RGBA[0] = RGBA[1] = RGBA[2] = RGBA[3] = 0.8f;
}

Color::Color(float R, float G, float B){
	RGBA[0] = R;
	RGBA[1] = G;
	RGBA[2] = B;
	RGBA[3] = 1.0f;
}

Color::Color(float R, float G, float B, float A){
	RGBA[0] = R;
	RGBA[1] = G;
	RGBA[2] = B;
	RGBA[3] = A;
}



Color::~Color(void)
{
}

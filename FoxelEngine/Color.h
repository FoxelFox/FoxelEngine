#pragma once
namespace GLSL{
	class Color{
	public:
		Color(void);
		Color(float R, float G, float B);
		Color(float R, float G, float B, float A);
		~Color(void);

		float RGBA[4];
	};
};

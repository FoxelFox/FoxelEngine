#version 150

uniform mat4 viewMatrix, projMatrix;

in vec3 in_Position;
in vec4 in_Color;
in vec3 in_Normal;

out vec4 ex_Color;

void main(void)
{
	ex_Color = vec4(in_Color);
	gl_Position = projMatrix * viewMatrix * vec4(in_Position, 1.0);
}

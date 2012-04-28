#version 150

uniform mat4 viewMatrix, projMatrix;
uniform vec3 player_position;
uniform vec3 chunk_Position;

in vec3 in_Position;
in vec4 in_Color;
in vec3 in_Normal;

vec3 lightPos;
vec3 g_lightPos = vec3(102400,51200,-102400);

out vec4 ex_Color;
float hsv,g_hsv;
float entf;
void main(void)
{
	// player light
	lightPos = player_position+chunk_Position;
	entf = distance(in_Position, lightPos);
	hsv = distance(in_Normal, normalize(in_Position - lightPos));
	
	// global light
	g_lightPos += chunk_Position;
	g_hsv = distance(in_Normal, normalize(g_lightPos));
	
	ex_Color = vec4(in_Color);
	ex_Color *= (g_hsv/8.0) + ((hsv/(entf/2.0)) * 4.0);
	
	gl_Position = projMatrix * viewMatrix * vec4(in_Position, 1.0);

	
}

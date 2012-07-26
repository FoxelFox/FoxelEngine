#version 330

uniform mat4 viewMatrix, projMatrix;
uniform vec3 player_position;
uniform vec3 chunk_Position;

in vec3 in_Position;
in vec4 in_Color;
in vec3 in_Normal;

vec3 lightPos;
vec3 g_lightPos = vec3(-102400,-51200,102400);

out vec3 ex_Normal;
out vec3 ex_Light;
out vec4 ex_Color;

float hsv,g_hsv;
float entf;
void main(void)
{
	// player light
	lightPos = player_position;
	entf = distance(in_Position, lightPos);
	hsv = dot(in_Normal, normalize(lightPos - in_Position));
	
	// global light
	g_hsv = clamp(dot(in_Normal, normalize(g_lightPos)),0.1,1.0);
	
	ex_Color = vec4(0.8,0.8,0.8,1.0);
	ex_Color *= clamp((g_hsv*0.25) + (hsv*0.25/(entf/16.0)),0.1,1.0);

	gl_Position = projMatrix * viewMatrix * vec4(in_Position, 1.0);

		ex_Light = normalize(lightPos - in_Position);
	ex_Normal = in_Normal;
}

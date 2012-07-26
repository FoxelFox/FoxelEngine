#version 330

in vec4 ex_Color;
layout(location = 0) out vec4 frag_Output;
layout(location = 1) out vec3 frag_Normal;
layout(location = 2) out vec3 frag_Position;

in vec3 ex_Position;
in vec3 ex_Normal;
in vec3 ex_Light;
in vec3 ex_Light_global;

void main(void){
	frag_Output = vec4(ex_Color.rgb,1.0) + ex_Color.a;
	frag_Normal = ex_Normal*0.5+0.5;
	frag_Position = ex_Position;
	//frag_Output.r += clamp(dot(ex_Normal,ex_Light),0.25,0.75)* 0.25;
	//frag_Output.g += clamp(dot(ex_Normal,ex_Light),0.25,0.75)* 0.25;
	//frag_Output.b += clamp(dot(ex_Normal,ex_Light),0.25,0.75)* 0.25;
}
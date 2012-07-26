#version 150

in vec4 ex_Color;
out vec4 frag_Output;

in vec3 ex_Normal;
in vec3 ex_Light;

void main(void){
	frag_Output = ex_Color;
	//frag_Output.r = clamp((dot(ex_Normal,ex_Light)),0.1,1);
	//frag_Output.g = clamp((dot(ex_Normal,ex_Light)),0.1,1);
	//frag_Output.b = clamp((dot(ex_Normal,ex_Light)),0.1,1);
}
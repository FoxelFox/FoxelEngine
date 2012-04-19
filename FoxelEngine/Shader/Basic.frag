#version 150
uniform vec4 test;

in vec4 ex_Color;
out vec4 fragOutput;

void main(void){
	fragOutput = ex_Color;
	//Try replacing the above with the following
	//vec3 tmp_Color;
	//tmp_Color = ex_Color.rrr;	
	//out_Color = vec4(tmp_Color,1.0);
}
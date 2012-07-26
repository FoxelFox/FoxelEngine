#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec2 uv;

void main(){
	gl_Position =  vec4(vertexPosition_modelspace,1);
	uv = (vertexPosition_modelspace.xy+vec2(1,1))/2.0;
}


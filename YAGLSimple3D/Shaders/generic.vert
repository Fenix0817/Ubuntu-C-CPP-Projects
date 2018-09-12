#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec3 inCol;
layout (location=2) in vec3 inNorm;

out vec3 col;
out vec3 normal;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

void main(){
	gl_Position=perspective*view*model*vec4(inPos,1.0);
	
	col=inCol;
	normal=inNorm;
}
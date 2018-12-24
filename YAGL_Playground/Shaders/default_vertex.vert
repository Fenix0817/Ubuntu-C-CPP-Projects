#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec2 inUV;
layout (location=2) in vec2 inNormUV;

out vec2 uv;
out vec2 normUV;

uniform mat4 MVP;

void main(){
	gl_Position=MVP*vec4(inPos,1.0);
	uv=inUV;
	normUV=inNormUV;
}
#version 450 core

layout (location=0) in vec2 inPos;
layout (location=1) in vec2 inUV;

uniform float size;

out vec2 uv;

void main(){
	gl_Position=vec4(size*inPos,0.0,1.0);
	uv=inUV;
}
#version 450 core

layout (location=0) in vec2 inPos;
layout (location=1) in vec3 inCol;

uniform vec2 size;

out vec3 col;

void main(){
	vec2 p=inPos;
	p/=size;
	p*=2.0;
	p-=1.0;
	gl_Position=vec4(p,0.0,1.0);
	col=inCol;
}
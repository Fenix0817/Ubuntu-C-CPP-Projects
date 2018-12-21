#version 450 core

layout (location=0) in vec2 inPos;

uniform vec2 pos;
uniform vec2 size;

out vec2 uv;

void main(){
	gl_Position=vec4((pos+size*inPos)*2.0-1.0,0.0,1.0);
	gl_Position.y*=-1.0;
	uv=inPos;
}
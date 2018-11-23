#version 450 core

layout (location=0) in vec3 inPos;

uniform vec3 offset;
uniform mat4 mvp;

void main(){
	gl_Position=mvp*vec4(offset+inPos*1.5-0.25,1.0);
}
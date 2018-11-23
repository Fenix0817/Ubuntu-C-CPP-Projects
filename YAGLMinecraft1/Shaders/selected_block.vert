#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec2 inUV;

uniform vec3 offset;
uniform mat4 mvp;

out vec2 uv;

uniform float scale;
//0,1 -> -scale,1+scale
void main(){
	gl_Position=mvp*vec4(offset+inPos*(2.0*scale+1.0)-scale,1.0);
	uv=inUV;
}
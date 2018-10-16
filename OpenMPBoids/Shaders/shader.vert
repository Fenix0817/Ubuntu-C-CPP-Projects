#version 450 core

layout (location=0) in vec2 inPos;
layout (location=1) in vec3 inCol;
layout (location=2) in float inSize;

out VS_OUT {
	vec3 color;
	float size;
} vs_out;

void main(){
	gl_Position=vec4(inPos,0.0,1.0);
	vs_out.color=inCol;
	vs_out.size=inSize;
}
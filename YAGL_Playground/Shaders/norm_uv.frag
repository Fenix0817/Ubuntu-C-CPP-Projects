#version 450 core

in vec2 normUV;

layout (location=0) out vec4 fragColor;

void main(){
	fragColor=vec4(normUV,0.0,1.0);
}
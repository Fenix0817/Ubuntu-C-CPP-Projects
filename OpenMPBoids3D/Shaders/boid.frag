#version 450 core

out vec4 fragColor;

in vec3 color;
in vec3 offset;

void main(){
	fragColor=vec4(offset,1.0);
}
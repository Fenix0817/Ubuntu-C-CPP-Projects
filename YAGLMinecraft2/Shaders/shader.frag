#version 450 core

out vec4 fragColor;

in vec3 vertPos;
in vec3 vertOffset;

void main(){
	fragColor=vec4(0.5+vertOffset,1.0);
}
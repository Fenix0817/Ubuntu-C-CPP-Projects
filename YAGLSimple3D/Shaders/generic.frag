#version 450 core

in vec3 col;
in vec3 normal;

out vec4 fragColor;

void main(){
	fragColor=vec4(col,1.0);
//	fragColor=vec4(0.5+0.5*normal,1.0);
}
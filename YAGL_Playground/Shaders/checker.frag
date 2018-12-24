#version 450 core

in vec2 uv;

layout (location=0) out vec4 fragColor;

uniform float uvScale;
uniform vec3 checkerLight;
uniform vec3 checkerDark;

void main(){
	vec2 c=floor(uv*uvScale);
	ivec2 ic=ivec2(c);
	if((ic.x+ic.y)%2==0)fragColor=vec4(checkerLight,1.0);
	else fragColor=vec4(checkerDark,1.0);
}
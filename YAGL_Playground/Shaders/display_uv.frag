#version 450 core

in vec2 uv;

layout (location=0) out vec4 fragColor;

uniform float uvScale;

void main(){
	fragColor=vec4(mod(uvScale*uv,1.0),0.0,1.0);
}
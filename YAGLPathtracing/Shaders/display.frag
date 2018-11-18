#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform float colorScale;

uniform sampler2D tex;

void main(){
	fragColor=texture(tex,uv)*colorScale;
}
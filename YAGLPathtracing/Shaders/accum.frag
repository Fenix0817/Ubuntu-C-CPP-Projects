#version 450 core

precision highp float;

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform float n;

void main(){
//	fragColor=(texture(tex1,uv)+texture(tex2,uv)*(n-1))/n;
	fragColor=texture(tex1,uv)+texture(tex2,uv);
}
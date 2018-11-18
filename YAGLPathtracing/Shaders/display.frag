#version 450 core

precision highp float;

in vec2 uv;

out vec4 fragColor;

uniform float n;

uniform sampler2D tex;

void main(){
	vec3 v=texture(tex,uv).xyz/n;
	if(v.x>1.0||v.y>1.0||v.z>1.0)v/=max(v.x,max(v.y,v.z));
	fragColor=vec4(v,1.0);
}
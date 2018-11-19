#version 450 core

precision highp float;

in vec2 uv;

out vec4 fragColor;

uniform float n;

uniform sampler2D tex;

uniform vec2 size;
uniform int uvMode;

void main(){
	vec2 uv_t=uv;
	if(uvMode==1)uv_t=round(uv*size)/size;
	uv_t=clamp(uv_t,vec2(0.0),vec2(1.0));
	vec3 v=texture(tex,uv_t).xyz/n;
	if(v.x>1.0||v.y>1.0||v.z>1.0)v/=max(v.x,max(v.y,v.z));
	fragColor=vec4(v,1.0);
}
#version 450 core

in vec2 uv;

uniform sampler2D tex;

out vec4 fragColor;

void main(){
	vec3 c=texture(tex,uv).xyz;
	if(c==vec3(1.0,1.0,1.0))discard;
	else fragColor=vec4(1.0);
}
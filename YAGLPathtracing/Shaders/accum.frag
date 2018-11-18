#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){
	fragColor=texture(tex1,uv)+texture(tex2,uv);
}
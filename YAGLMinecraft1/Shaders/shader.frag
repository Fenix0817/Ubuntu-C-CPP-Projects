#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex;

void main(){
	//fragColor=vec4(uv,0.0,1.0);
	fragColor=texture(tex,uv);
}
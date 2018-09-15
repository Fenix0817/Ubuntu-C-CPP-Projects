#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float mixValue;

void main(){
//	fragColor=vec4(uv,0.0,1.0);
	fragColor=mix(texture(tex1,uv),texture(tex2,uv),mixValue);
}
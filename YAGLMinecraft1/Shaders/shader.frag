#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	//fragColor=vec4(uv,0.0,1.0);
	fragColor=texture(tex,uv);
	float fogFactor=clamp(0.01*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	fragColor=mix(fragColor,fogColor,fogFactor);
}
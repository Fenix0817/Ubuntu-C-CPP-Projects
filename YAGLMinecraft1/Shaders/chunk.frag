#version 450 core

in vec2 uv;
in float ao;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	fragColor=texture(tex,uv);
	float fogFactor=clamp(0.01*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	fragColor*=clamp(ao,0.25,1.0);
//	fragColor*=ao;
	fragColor=mix(fragColor,fogColor,fogFactor);
	
}
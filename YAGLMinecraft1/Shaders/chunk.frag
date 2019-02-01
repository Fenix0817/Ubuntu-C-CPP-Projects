#version 450 core

in vec2 uv;
in float ao;
in float torchlight;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	fragColor=texture(tex,uv);
	float fogFactor=clamp(0.01*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	
	float aoFactor=clamp(ao+.25,0.0,1.0);
	float lightFactor=clamp(torchlight,0.2,1.0);
	
	fragColor*=aoFactor*lightFactor;
	
	fragColor=mix(fragColor,fogColor,fogFactor);
	
}
#version 450 core

in vec2 uv;
in float ao;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	fragColor=texture(tex,uv);
	float fogFactor=clamp(0.02*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	fragColor*=clamp(ao,0.5,1.0);
	fragColor=vec4(abs(ao));
	if(ao<0.0)fragColor.yz=vec2(0.0);
	fragColor=mix(fragColor,fogColor,fogFactor);
	
}
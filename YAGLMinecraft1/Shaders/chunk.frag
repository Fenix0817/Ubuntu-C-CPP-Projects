#version 450 core

in vec2 uv;
in float ao;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	//fragColor=vec4(uv,0.0,1.0);
	fragColor=texture(tex,uv);
	//fragColor.xyz*=clamp(ao,0.0,1.0)*0.3+clamp(light,0.0,1.0)*0.7;
	//fragColor.xyz*=ao;
	//fragColor.xyz/=max(fragColor.x,max(fragColor.y,fragColor.z));
	float fogFactor=clamp(0.02*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	//float fogFactor=0.0;
	fragColor*=clamp(ao,0.5,1.0);
	//fragColor=vec4(abs(ao));
	if(ao<0.0)fragColor.yz=vec2(0.0);
	fragColor=mix(fragColor,fogColor,fogFactor);
	
}
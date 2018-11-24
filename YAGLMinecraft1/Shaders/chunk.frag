#version 450 core

in vec2 uv;
flat in float light;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	//fragColor=vec4(uv,0.0,1.0);
	fragColor=texture(tex,uv);
	//fragColor.xyz/=max(fragColor.x,max(fragColor.y,fragColor.z));
	float fogFactor=clamp(0.01*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	//float fogFactor=0.0;
	fragColor=mix(fragColor,fogColor,fogFactor)*light;
}
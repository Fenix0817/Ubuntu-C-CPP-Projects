#version 450 core

in vec2 uv;
in float light;
in float ao;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec4 fogColor;

void main(){
	//fragColor=vec4(uv,0.0,1.0);
	fragColor=texture(tex,uv);
	//fragColor.xyz*=ao*0.3+light*0.7;
	fragColor.xyz*=ao;
	if(light>1.0)fragColor.xyz=vec3(1.0,0.0,0.0);
	//fragColor.xyz/=max(fragColor.x,max(fragColor.y,fragColor.z));
	//float fogFactor=clamp(0.02*gl_FragCoord.z/gl_FragCoord.w,0.0,1.0);
	float fogFactor=0.0;
	fragColor=mix(fragColor,fogColor,fogFactor);
}
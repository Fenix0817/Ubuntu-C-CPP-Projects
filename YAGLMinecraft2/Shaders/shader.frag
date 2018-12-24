#version 450 core

out vec4 fragColor;

in vec3 vertPos;
in vec3 vertOffset;
in vec2 vertUV;

uniform sampler2D atlasTex;

void main(){
	//fragColor=vec4(0.5+vertOffset,1.0);
	//fragColor=vec4(vertUV,0.0,1.0);
	fragColor=texture(atlasTex,vertUV);
	if(fragColor.xyz==vec3(1.0,0.0,1.0))discard;
}
#version 450 core

in vec2 uv;

uniform sampler2D tex;

out vec4 fragColor;

void main(){
	fragColor=texture(tex,vec2(uv.x,1.0-uv.y));
	if(fragColor.xyz==vec3(0.0)){
		discard;
	}
}
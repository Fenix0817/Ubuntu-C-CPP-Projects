#version 450 core

out vec4 fragColor;

in vec3 color;
in vec3 offset;
in vec3 normal;
in vec3 pos;

void main(){
	vec3 ray=normalize(vec3(0.5)-pos);
	float diffuse=clamp(dot(ray,normal),0.0,1.0)*1.5+0.1;
	//fragColor=vec4(0.5+0.5*normal,1.0);
	fragColor=vec4(diffuse,diffuse,diffuse,1.0);
}
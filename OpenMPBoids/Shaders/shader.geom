#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in VS_OUT {
	vec3 color;
	float size;
} gs_in[];

out vec3 color;

void vert(vec2 p){
	gl_Position=vec4(p,0.0,1.0);
	color=gs_in[0].color;
	EmitVertex();
}

void end(){
	EndPrimitive();
}

void main() {
	vec2 pos=gl_in[0].gl_Position.xy;
	float size=gs_in[0].size;
	vert(pos-vec2(size,size));
	vert(pos-vec2(size,.0));
	vert(pos-vec2(.0,size));
	end();
}
#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in VS_OUT {
	vec3 color;
	float size;
	vec2 dir;
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
	vec2 dir=normalize(gs_in[0].dir);
	//vec2 dir=vec2(1.0,0.0);
	if(gs_in[0].dir==vec2(0.0,0.0))dir=vec2(1.0,0.0);
	float size=gs_in[0].size;
	
	vec2 ldir=vec2(-dir.y,dir.x);
	vert(pos+dir*size);
	vert(pos+ldir*.25*size);
	vert(pos-ldir*.25*size);
	end();
}
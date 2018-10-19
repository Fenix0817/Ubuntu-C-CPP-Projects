#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=24) out;

in VS_OUT {
	vec3 color;
	float size;
	vec3 dir;
} gs_in[];

out vec3 color;
out vec3 offset;

uniform mat4 perspective;
uniform mat4 view;

void vert(float x,float y,float z){
	offset=vec3(x,y,z);
	gl_Position=perspective*view*vec4(gl_in[0].gl_Position.xyz+offset*gs_in[0].size,1.0);
	color=gs_in[0].color;
	EmitVertex();
}

void end(){
	EndPrimitive();
}

void main(){
	vec3 pos=gl_in[0].gl_Position.xyz;
	vec3 dir=normalize(gs_in[0].dir);
	if(gs_in[0].dir==vec3(0.0,0.0,0.0))dir=vec3(1.0,0.0,0.0);
	float size=gs_in[0].size;

	vert(0.0,0.0,0.0);
	vert(1.0,0.0,0.0);
	vert(0.0,1.0,0.0);
	vert(1.0,1.0,0.0);
	end();

	vert(0.0,0.0,1.0);
	vert(1.0,0.0,1.0);
	vert(0.0,1.0,1.0);
	vert(1.0,1.0,1.0);
	end();

	vert(0.0,0.0,0.0);
	vert(0.0,1.0,0.0);
	vert(0.0,0.0,1.0);
	vert(0.0,1.0,1.0);
	end();

	vert(1.0,0.0,0.0);
	vert(1.0,1.0,0.0);
	vert(1.0,0.0,1.0);
	vert(1.0,1.0,1.0);
	end();

	vert(0.0,0.0,0.0);
	vert(1.0,0.0,0.0);
	vert(0.0,0.0,1.0);
	vert(1.0,0.0,1.0);
	end();

	vert(0.0,1.0,0.0);
	vert(1.0,1.0,0.0);
	vert(0.0,1.0,1.0);
	vert(1.0,1.0,1.0);
	end();

}
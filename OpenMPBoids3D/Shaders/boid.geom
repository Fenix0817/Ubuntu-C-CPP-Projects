#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=200) out;

in VS_OUT {
	vec3 color;
	float size;
	vec3 dir;
} gs_in[];

out vec3 color;
out vec3 offset;
out vec3 normal;
out vec3 pos;

uniform mat4 perspective;
uniform mat4 view;

void vert(float x,float y,float z){
	offset=vec3(x,y,z);
	gl_Position=perspective*view*vec4(gl_in[0].gl_Position.xyz+offset*gs_in[0].size,1.0);
	pos=offset+gl_in[0].gl_Position.xyz;
	color=gs_in[0].color;
	EmitVertex();
}

#define detail_theta 3.0
#define detail_phi 6.0
#define twopi 6.28318530718
#define pi 3.14159265359

void sphereVert(float i,float j){
	float theta=i*pi/detail_theta;
	float phi=j*twopi/detail_phi;
	
	float costheta=cos(theta);
	float sintheta=sin(theta);
	float cosphi=cos(phi);
	float sinphi=sin(phi);
	vec3 v=vec3(sintheta*cosphi,sintheta*sinphi,costheta);
	normal=v;
	vert(v.x,v.y,v.z);
}

void end(){
	EndPrimitive();
}

void main(){
	vec3 pos=gl_in[0].gl_Position.xyz;
	vec3 dir=normalize(gs_in[0].dir);
	if(gs_in[0].dir==vec3(0.0,0.0,0.0))dir=vec3(1.0,0.0,0.0);
	float size=gs_in[0].size;
	
	for(float i=0.0;i<detail_theta;i+=1.0){
		for(float j=0.0;j<detail_phi;j+=1.0){
			sphereVert(i,j);
			sphereVert(i+1.0,j);
			sphereVert(i,j+1.0);
			sphereVert(i+1.0,j+1.0);
			end();
		}
	}


	// vert(0.0,0.0,0.0);
	// vert(1.0,0.0,0.0);
	// vert(0.0,1.0,0.0);
	// vert(1.0,1.0,0.0);
	// end();

	// vert(0.0,0.0,1.0);
	// vert(1.0,0.0,1.0);
	// vert(0.0,1.0,1.0);
	// vert(1.0,1.0,1.0);
	// end();

	// vert(0.0,0.0,0.0);
	// vert(0.0,1.0,0.0);
	// vert(0.0,0.0,1.0);
	// vert(0.0,1.0,1.0);
	// end();

	// vert(1.0,0.0,0.0);
	// vert(1.0,1.0,0.0);
	// vert(1.0,0.0,1.0);
	// vert(1.0,1.0,1.0);
	// end();

	// vert(0.0,0.0,0.0);
	// vert(1.0,0.0,0.0);
	// vert(0.0,0.0,1.0);
	// vert(1.0,0.0,1.0);
	// end();

	// vert(0.0,1.0,0.0);
	// vert(1.0,1.0,0.0);
	// vert(0.0,1.0,1.0);
	// vert(1.0,1.0,1.0);
	// end();

}
#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=24) out;

in VertexOut {
	vec3 pos;
	int xmi,xpl,ymi,ypl,zmi,zpl;
} vout[];

uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;

out vec3 vertPos;
out vec3 vertOffset;

void emit(vec3 p,vec3 o){
	gl_Position=perspectiveMatrix*viewMatrix*vec4(p+o,1.0);
	vertPos=p;
	vertOffset=o;
	EmitVertex();
}

void end(){
	EndPrimitive();
}

//  Triangle strip output layout:
//  0 ------- 1
//  |      /  |
//  |    /    |
//  |  /      |
//  2 ------- 3

void main(){
	for(int i=0;i<1;i++){
		vec3 pos=vout[i].pos;
		int xmi=vout[i].xmi;
		int xpl=vout[i].xpl;
		int ymi=vout[i].ymi;
		int ypl=vout[i].ypl;
		int zmi=vout[i].zmi;
		int zpl=vout[i].zpl;
		if(xmi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5));
			emit(pos,vec3(-0.5, 0.5,-0.5));
			emit(pos,vec3(-0.5,-0.5, 0.5));
			emit(pos,vec3(-0.5, 0.5, 0.5));
			end();
		}
		if(xpl!=0){
			emit(pos,vec3( 0.5,-0.5,-0.5));
			emit(pos,vec3( 0.5, 0.5,-0.5));
			emit(pos,vec3( 0.5,-0.5, 0.5));
			emit(pos,vec3( 0.5, 0.5, 0.5));
			end();
		}
		if(ymi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5));
			emit(pos,vec3( 0.5,-0.5,-0.5));
			emit(pos,vec3(-0.5,-0.5, 0.5));
			emit(pos,vec3( 0.5,-0.5, 0.5));
			end();
		}
		if(ypl!=0){
			emit(pos,vec3(-0.5, 0.5,-0.5));
			emit(pos,vec3( 0.5, 0.5,-0.5));
			emit(pos,vec3(-0.5, 0.5, 0.5));
			emit(pos,vec3( 0.5, 0.5, 0.5));
			end();
		}
		if(zmi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5));
			emit(pos,vec3( 0.5,-0.5,-0.5));
			emit(pos,vec3(-0.5, 0.5,-0.5));
			emit(pos,vec3( 0.5, 0.5,-0.5));
			end();
		}
		if(zpl!=0){
			emit(pos,vec3(-0.5,-0.5, 0.5));
			emit(pos,vec3( 0.5,-0.5, 0.5));
			emit(pos,vec3(-0.5, 0.5, 0.5));
			emit(pos,vec3( 0.5, 0.5, 0.5));
			end();
		}
	}
}
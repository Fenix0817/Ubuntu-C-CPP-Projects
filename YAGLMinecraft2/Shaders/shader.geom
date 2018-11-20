#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=100) out;

in VertexOut {
	vec3 pos;
	int xmi,xpl,ymi,ypl,zmi,zpl;
	vec4 uv_xmi,uv_xpl,uv_ymi,uv_ypl,uv_zmi,uv_zpl;
} vout[];

uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;

out vec3 vertPos;
out vec3 vertOffset;
out vec2 vertUV;

void emit(vec3 p,vec3 o,vec4 uv,vec2 uv_o){
	gl_Position=perspectiveMatrix*viewMatrix*vec4(p+o,1.0);
	vertPos=p;
	vertOffset=o;
	vertUV=uv.xy+uv.zw*uv_o;
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
		vec4 uv_xmi=vout[i].uv_xmi;
		vec4 uv_xpl=vout[i].uv_xpl;
		vec4 uv_ymi=vout[i].uv_ymi;
		vec4 uv_ypl=vout[i].uv_ypl;
		vec4 uv_zmi=vout[i].uv_zmi;
		vec4 uv_zpl=vout[i].uv_zpl;
		if(xmi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5),uv_xmi,vec2(1.0,1.0));
			emit(pos,vec3(-0.5, 0.5,-0.5),uv_xmi,vec2(1.0,0.0));
			emit(pos,vec3(-0.5,-0.5, 0.5),uv_xmi,vec2(0.0,1.0));
			emit(pos,vec3(-0.5, 0.5, 0.5),uv_xmi,vec2(0.0,0.0));
			end();
		}
		if(xpl!=0){//needs rotation
			emit(pos,vec3( 0.5,-0.5,-0.5),uv_xpl,vec2(1.0,1.0));
			emit(pos,vec3( 0.5, 0.5,-0.5),uv_xpl,vec2(1.0,0.0));
			emit(pos,vec3( 0.5,-0.5, 0.5),uv_xpl,vec2(0.0,1.0));
			emit(pos,vec3( 0.5, 0.5, 0.5),uv_xpl,vec2(0.0,0.0));
			end();
		}
		if(ymi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5),uv_ymi,vec2(0.0,0.0));
			emit(pos,vec3( 0.5,-0.5,-0.5),uv_ymi,vec2(1.0,0.0));
			emit(pos,vec3(-0.5,-0.5, 0.5),uv_ymi,vec2(0.0,1.0));
			emit(pos,vec3( 0.5,-0.5, 0.5),uv_ymi,vec2(1.0,1.0));
			end();
		}
		if(ypl!=0){
			emit(pos,vec3(-0.5, 0.5,-0.5),uv_ypl,vec2(0.0,0.0));
			emit(pos,vec3( 0.5, 0.5,-0.5),uv_ypl,vec2(1.0,0.0));
			emit(pos,vec3(-0.5, 0.5, 0.5),uv_ypl,vec2(0.0,1.0));
			emit(pos,vec3( 0.5, 0.5, 0.5),uv_ypl,vec2(1.0,1.0));
			end();
		}
		if(zmi!=0){
			emit(pos,vec3(-0.5,-0.5,-0.5),uv_zmi,vec2(0.0,1.0));
			emit(pos,vec3( 0.5,-0.5,-0.5),uv_zmi,vec2(1.0,1.0));
			emit(pos,vec3(-0.5, 0.5,-0.5),uv_zmi,vec2(0.0,0.0));
			emit(pos,vec3( 0.5, 0.5,-0.5),uv_zmi,vec2(1.0,0.0));
			end();
		}
		if(zpl!=0){
			emit(pos,vec3(-0.5,-0.5, 0.5),uv_zpl,vec2(0.0,1.0));
			emit(pos,vec3( 0.5,-0.5, 0.5),uv_zpl,vec2(1.0,1.0));
			emit(pos,vec3(-0.5, 0.5, 0.5),uv_zpl,vec2(0.0,0.0));
			emit(pos,vec3( 0.5, 0.5, 0.5),uv_zpl,vec2(1.0,0.0));
			end();
		}
	}
}
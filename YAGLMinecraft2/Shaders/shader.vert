#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in int inXMI;
layout (location=2) in int inXPL;
layout (location=3) in int inYMI;
layout (location=4) in int inYPL;
layout (location=5) in int inZMI;
layout (location=6) in int inZPL;
layout (location=7) in vec4 inUVXMI;
layout (location=8) in vec4 inUVXPL;
layout (location=9) in vec4 inUVYMI;
layout (location=10) in vec4 inUVYPL;
layout (location=11) in vec4 inUVZMI;
layout (location=12) in vec4 inUVZPL;

out VertexOut {
	vec3 pos;
	int xmi,xpl,ymi,ypl,zmi,zpl;
	vec4 uv_xmi,uv_xpl,uv_ymi,uv_ypl,uv_zmi,uv_zpl;
} vout;

void main(){
	vout.pos=inPos;
	vout.xmi=inXMI;
	vout.xpl=inXPL;
	vout.ymi=inYMI;
	vout.ypl=inYPL;
	vout.zmi=inZMI;
	vout.zpl=inZPL;
	vout.uv_xmi=inUVXMI;
	vout.uv_xpl=inUVXPL;
	vout.uv_ymi=inUVYMI;
	vout.uv_ypl=inUVYPL;
	vout.uv_zmi=inUVZMI;
	vout.uv_zpl=inUVZPL;
}
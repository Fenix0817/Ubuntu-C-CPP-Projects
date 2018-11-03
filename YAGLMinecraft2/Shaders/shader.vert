#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in int inXMI;
layout (location=2) in int inXPL;
layout (location=3) in int inYMI;
layout (location=4) in int inYPL;
layout (location=5) in int inZMI;
layout (location=6) in int inZPL;

out VertexOut {
	vec3 pos;
	int xmi,xpl,ymi,ypl,zmi,zpl;
} vout;

void main(){
	vout.pos=inPos;
	vout.xmi=inXMI;
	vout.xpl=inXPL;
	vout.ymi=inYMI;
	vout.ypl=inYPL;
	vout.zmi=inZMI;
	vout.zpl=inZPL;
}
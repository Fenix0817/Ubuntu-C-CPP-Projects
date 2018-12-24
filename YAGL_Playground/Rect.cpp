/*
 * Rect.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#include "Rect.h"

Rect::Rect() {
	// TODO Auto-generated constructor stub

}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Rect::intersect(glm::vec3 ro,glm::vec3 rd){
	glm::vec3 n=glm::cross(a(),b());
	float t=glm::dot(pos()-ro,n)/dot(rd,n);
	return ro+t*rd;
}

void Rect::init(float x,float y,float z,float ax,float ay,float az,float bx,float by,float bz){
	this->x=x;
	this->y=y;
	this->z=z;
	this->ax=ax;
	this->ay=ay;
	this->az=az;
	this->bx=bx;
	this->by=by;
	this->bz=bz;

	float posData[]={
			x,y,z,
			x+ax,y+ay,z+az,
			x+ax+bx,y+ay+by,z+az+bz,
			x+bx,y+by,z+bz
	};

	float a=sqrt(ax*ax+ay*ay+az*az);
	float b=sqrt(bx*bx+by*by+bz*bz);

	float uvData[]={
			0,0,
			a,0,
			a,b,
			0,b
	};

	float normUVData[]={
			0,0,
			1,0,
			1,1,
			0,1
	};

	unsigned int triData[]={
			0,1,2,
			0,2,3
	};

	vao.create();
	vao.bind();

	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();

	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.addVertexAttrib(1,2,false,2,(const GLvoid*)0);
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.unbind();

	vboNormUV.setTarget(gl::VertexBufferTarget::Array);
	vboNormUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboNormUV.setType(gl::Type::Float);
	vboNormUV.create();
	vboNormUV.bind();
	vboNormUV.addVertexAttrib(2,2,false,2,(const GLvoid*)0);
	vboNormUV.setData(sizeof(normUVData),normUVData);
	vboNormUV.unbind();

	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}
void Rect::render(){
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}

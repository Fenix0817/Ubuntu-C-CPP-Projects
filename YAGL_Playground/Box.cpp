/*
 * Box.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: jack
 */

#include "Box.h"

Box::Box() {
	// TODO Auto-generated constructor stub

}

Box::~Box() {
	// TODO Auto-generated destructor stub
}

void Box::init(float x,float y,float z,float sx,float sy,float sz){
	this->x=x;
	this->y=y;
	this->z=z;
	this->sx=sx;
	this->sy=sy;
	this->sz=sz;
	float posData[]={
			//xmi
			x,y,z,
			x,y+sy,z,
			x,y+sy,z+sz,
			x,y,z+sz,
			//xpl
			x+sx,y,z,
			x+sx,y+sy,z,
			x+sx,y+sy,z+sz,
			x+sx,y,z+sz,
			//ymi
			x,y,z,
			x+sx,y,z,
			x+sx,y,z+sz,
			x,y,z+sz,
			//ypl
			x,y+sy,z,
			x+sx,y+sy,z,
			x+sx,y+sy,z+sz,
			x,y+sy,z+sz,
			//zmi
			x,y,z,
			x+sx,y,z,
			x+sx,y+sy,z,
			x,y+sy,z,
			//zpl
			x,y,z+sz,
			x+sx,y,z+sz,
			x+sx,y+sy,z+sz,
			x,y+sy,z+sz
	};

	float uvData[]={
			//xmi
			0,0,
			sy,0,
			sy,sz,
			0,sz,
			//xpl
			0,0,
			sy,0,
			sy,sz,
			0,sz,
			//ymi
			0,0,
			sx,0,
			sx,sz,
			0,sz,
			//ypl
			0,0,
			sx,0,
			sx,sz,
			0,sz,
			//zmi
			0,0,
			sx,0,
			sx,sy,
			0,sy,
			//zpl
			0,0,
			sx,0,
			sx,sy,
			0,sy
	};

	float normUVData[]={
			//xmi
			0,0,
			1,0,
			1,1,
			0,1,
			//xpl
			0,0,
			1,0,
			1,1,
			0,1,
			//ymi
			0,0,
			1,0,
			1,1,
			0,1,
			//ypl
			0,0,
			1,0,
			1,1,
			0,1,
			//zmi
			0,0,
			1,0,
			1,1,
			0,1,
			//zpl
			0,0,
			1,0,
			1,1,
			0,1
	};

	unsigned int triData[]={
			//xmi
			0,1,2,
			0,2,3,
			//xpl
			4,5,6,
			4,6,7,
			//ymi
			8,9,10,
			8,10,11,
			//ypl
			12,13,14,
			12,14,15,
			//zmi
			16,17,18,
			16,18,19,
			//zpl
			20,21,22,
			20,22,23
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
void Box::render(){
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}

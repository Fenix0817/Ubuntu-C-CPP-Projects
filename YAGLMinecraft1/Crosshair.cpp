/*
 * Crosshair.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: jack
 */

#include "Crosshair.h"

Crosshair::Crosshair() {
	// TODO Auto-generated constructor stub

}

Crosshair::~Crosshair() {
	// TODO Auto-generated destructor stub
}

void Crosshair::init(){
	tex=gl::loadTexture("Assets/crosshair.png");

	shader.create();
	shader.attachFile("Shaders/crosshair.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/crosshair.frag",gl::ShaderType::Fragment);
	shader.link();

	float posData[]={
			-1,-1,
			-1, 1,
			 1, 1,
			 1,-1
	};

	float uvData[]={
			0,0,
			0,1,
			1,1,
			1,0
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
	vboPos.addVertexAttrib(0,2,false,2,(const GLvoid*)0);
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

	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}
void Crosshair::render(){
	shader.bind();
	shader.setFloat("size",0.03);

	tex.bindToUnit(0);
	shader.setInt("tex",0);

	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
	shader.unbind();
}

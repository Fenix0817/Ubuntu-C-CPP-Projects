/*
 * RGBCube.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: jack
 */

#include "RGBCube.h"

RGBCube::RGBCube() {
	// TODO Auto-generated constructor stub

}

RGBCube::~RGBCube() {
	// TODO Auto-generated destructor stub
}

void RGBCube::init(){
	shader.create();
	shader.attachFile("Shaders/generic.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/generic.frag",gl::ShaderType::Fragment);
	shader.link();

	//rgb cube
	float posData[]={
			-1,-1,-1,
			-1,-1, 1,
			-1, 1,-1,
			-1, 1, 1,

			 1,-1,-1,
			 1,-1, 1,
			 1, 1,-1,
			 1, 1, 1,

			-1,-1,-1,
			-1,-1, 1,
			 1,-1,-1,
			 1,-1, 1,

			-1, 1,-1,
			-1, 1, 1,
			 1, 1,-1,
			 1, 1, 1,

			-1,-1,-1,
			-1, 1,-1,
			 1,-1,-1,
			 1, 1,-1,

			-1,-1, 1,
			-1, 1, 1,
			 1,-1, 1,
			 1, 1, 1
	};

	float colData[]={
			0,0,0,
			0,0,1,
			0,1,0,
			0,1,1,

			1,0,0,
			1,0,1,
			1,1,0,
			1,1,1,

			0,0,0,
			0,0,1,
			1,0,0,
			1,0,1,

			0,1,0,
			0,1,1,
			1,1,0,
			1,1,1,

			0,0,0,
			0,1,0,
			1,0,0,
			1,1,1,
			0,0,1,
			0,1,1,
			1,0,1,
			1,1,1
	};

	float normalData[]={
			-1,0,0,
			-1,0,0,
			-1,0,0,
			-1,0,0,

			 1,0,0,
			 1,0,0,
			 1,0,0,
			 1,0,0,

			0,-1,0,
			0,-1,0,
			0,-1,0,
			0,-1,0,

			0, 1,0,
			0, 1,0,
			0, 1,0,
			0, 1,0,

			0,0,-1,
			0,0,-1,
			0,0,-1,
			0,0,-1,

			0,0, 1,
			0,0, 1,
			0,0, 1,
			0,0, 1
	};

	unsigned int triData[]={
			0,1,2,
			1,2,3,

			4,5,6,
			5,6,7,

			8,9,10,
			9,10,11,

			12,13,14,
			13,14,15,

			16,17,18,
			17,18,19,

			20,21,22,
			21,22,23
	};

	vao.create();
	vao.bind();

	vboPos=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,3,false,3,0);
	vboPos.unbind();

	vboCol=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboCol.create();
	vboCol.bind();
	vboCol.setData(sizeof(colData),colData);
	vboCol.addVertexAttrib(1,3,false,3,0);
	vboCol.unbind();

	vboNorm=gl::VertexBuffer(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboNorm.create();
	vboNorm.bind();
	vboNorm.setData(sizeof(normalData),normalData);
	vboNorm.addVertexAttrib(2,3,true,3,0);
	vboNorm.unbind();

	ebo=gl::VertexBuffer(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}

void RGBCube::render(glm::mat4 perspective,glm::mat4 view,glm::mat4 model){
	shader.bind();

	shader.setMat4("perspective",perspective);
	shader.setMat4("view",view);
	shader.setMat4("model",model);

	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
	shader.unbind();
}

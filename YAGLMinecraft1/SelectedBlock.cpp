/*
 * SelectedBlock.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: jack
 */

#include "SelectedBlock.h"

SelectedBlock::SelectedBlock() {
	// TODO Auto-generated constructor stub

}

SelectedBlock::~SelectedBlock() {
	// TODO Auto-generated destructor stub
}

void SelectedBlock::init(){
	shader.create();
	shader.attachFile("Shaders/selected_block.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/selected_block.frag",gl::ShaderType::Fragment);
	shader.link();

	float posData[]={
			0,0,0,
			1,0,0,
			0,1,0,
			1,1,0,

			0,0,1,
			1,0,1,
			0,1,1,
			1,1,1,

			0,0,0,
			0,1,0,
			0,0,1,
			0,1,1,

			1,0,0,
			1,1,0,
			1,0,1,
			1,1,1,

			0,0,0,
			1,0,0,
			0,0,1,
			1,0,1,

			0,1,0,
			1,1,0,
			0,1,1,
			1,1,1
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

	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPos.setData(sizeof(posData),posData);
	vboPos.unbind();

	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}

void SelectedBlock::render(float x,float y,float z,Camera cam){
	shader.bind();

	shader.setVec3("offset",x,y,z);
	shader.setMat4("mvp",cam.getPerspectiveViewMatrix());

	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
	shader.unbind();
}


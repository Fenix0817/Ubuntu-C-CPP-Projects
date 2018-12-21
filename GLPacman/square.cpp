/*
 * square.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#include "square.h"

gl::VertexArray*vao=nullptr;

void initSquare(){
	vao=new gl::VertexArray();
	vao->create();
	vao->bind();

	float data[]={
			0,0,
			0,1,
			1,1,

			0,0,
			1,0,
			1,1
	};

	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Float);
	vbo.create();
	vbo.bind();
	vbo.setData(sizeof(data),data);
	vbo.addVertexAttrib(0,2,false,2,nullptr);
	vbo.unbind();

	vao->unbind();
}

void renderSquare(){
	vao->bind();
	glDrawArrays(GL_TRIANGLES,0,6);
	vao->unbind();
}

void deleteSquare(){
	delete vao;
}

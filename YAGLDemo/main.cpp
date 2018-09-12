/*
 * main.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: jack
 */


#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Utilities.h"
#include <stdio.h>
#include <math.h>

int main(){

	gl::init();
	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Demo");
	window.setSize(500,500);

	window.bind();

	printf("Major version ..... %i\n",gl::majorVersion());
	printf("Minor version ..... %i\n",gl::minorVersion());
	printf("Version ........... %s\n",gl::version());
	printf("Vendor ............ %s\n",gl::vendor());
	printf("Renderer .......... %s\n",gl::renderer());

	const char*vertSource="#version 450\nlayout (location=0) in vec3 inPos;layout (location=1)in vec3 inCol;out vec3 col;void main(){gl_Position=vec4(inPos,1.0);col=inCol;}";
	const char*fragSource="#version 450\nout vec4 fc;in vec3 col;void main(){fc=vec4(col,1.0);}";

	gl::Shader shader;
	shader.create();
	shader.attach(vertSource, gl::ShaderType::Vertex);
	shader.attach(fragSource, gl::ShaderType::Fragment);
	shader.link();

	float posData[]={
			-0.6,-0.6,0,
			-0.6, 0.6,0,
			 0.6,-0.6,0,
			 0.6, 0.6,0
	};

	float colData[]={
			1,0,0,
			0,1,0,
			0,0,1,
			1,1,1
	};

	unsigned int triData[]={
			0,1,2,
			1,2,3
	};

	gl::VertexArray vao;
	vao.create();
	vao.bind();

	gl::VertexBuffer vboPos(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,3,false,3,(void*)0);
	vboPos.unbind();

	gl::VertexBuffer vboCol(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboCol.create();
	vboCol.bind();
	vboCol.setData(sizeof(colData),colData);
	vboCol.addVertexAttrib(1,3,false,3,(void*)0);
	vboCol.unbind();

	gl::VertexBuffer ebo(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();

	printf("vao=%i\nvboPos=%i\nvboCol=%i\nshader=%i\n",vao.id,vboPos.id,vboCol.id,shader.id);

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(0.5+0.5*cos(gl::time()));
		gl::clearScreen();

		glViewport(0,0,500,500);

		shader.bind();
		vao.bind();
//		glDrawArrays(GL_IANGLES,0,3);
		ebo.bind();
		ebo.render();
		ebo.unbind();
		vao.unbind();
		shader.unbind();

		window.unbind();
	}

	gl::end();

	return 0;
}

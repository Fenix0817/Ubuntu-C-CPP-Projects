/*
 * main.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

int main(){
	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setSize(500,500);
	window.setTitle("YAGL Texture Demo");
	window.bind();

	gl::VertexArray vao;
	vao.create();
	vao.bind();

	float posData[]={
			-1,-1,0,
			 1,-1,0,
			-1, 1,0,
			 1, 1,0
	};

	float uvData[]={
			0,0,
			1,0,
			0,1,
			1,1
	};

	unsigned int triData[]={
			0,1,2,
			1,2,3
	};

	gl::VertexBuffer vboPos;
	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,3,false,3,0);
	vboPos.unbind();

	gl::VertexBuffer vboUV;
	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.addVertexAttrib(1,2,false,2,0);
	vboUV.unbind();

	gl::VertexBuffer ebo;
	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.link();

	gl::Texture tex1=gl::loadTexture("Images/ubuntu.png");
	gl::Texture tex2=gl::loadTexture("Images/apple.png");
	window.unbind();

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(1);
		gl::clearScreen();
		gl::defaultViewport(window);

		shader.bind();

		tex1.bindToUnit(0);
		shader.setInt("tex1",0);

		tex2.bindToUnit(1);
		shader.setInt("tex2",1);

		shader.setFloat("mixValue",0.5+0.5*cos(gl::time()));

		vao.bind();
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



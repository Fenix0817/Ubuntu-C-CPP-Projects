/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#include <stdio.h>
#include "Window.h"
#include "Utilities.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

int main(){
#pragma omp parallel for
	for(int i=0;i<10;i++){
		printf("%i\n",i);
	}

	gl::init();
	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(1);
	window.create();
	window.setTitle("Boids and OpenMP");
	window.setSize(500,500);

	window.bind();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.attachFile("Shaders/shader.geom",gl::ShaderType::Geometry);
	shader.link();

	int n=20;
	float pos[n*2];
	for(int i=0;i<n;i++){
		pos[i*2+0]=2*((float)rand())/((float)RAND_MAX)-1;
		pos[i*2+1]=2*((float)rand())/((float)RAND_MAX)-1;
	}
	float col[n*3];
	for(int i=0;i<n;i++){
		col[i*3+0]=((float)rand())/((float)RAND_MAX);
		col[i*3+1]=((float)rand())/((float)RAND_MAX);
		col[i*3+2]=((float)rand())/((float)RAND_MAX);
	}
	float size[n];
	for(int i=0;i<n;i++){
		size[i]=0.05+0.1*((float)rand())/((float)RAND_MAX);
	}

	gl::VertexArray vao;
	vao.create();
	vao.bind();

	gl::VertexBuffer vboPos;
	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.addVertexAttrib(0,2,false,2,(const GLvoid*)0);
	vboPos.setData(sizeof(pos),pos);
	vboPos.unbind();

	gl::VertexBuffer vboCol;
	vboCol.setTarget(gl::VertexBufferTarget::Array);
	vboCol.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboCol.setType(gl::Type::Float);
	vboCol.create();
	vboCol.bind();
	vboCol.addVertexAttrib(1,3,false,3,(const GLvoid*)0);
	vboCol.setData(sizeof(col),col);
	vboCol.unbind();

	gl::VertexBuffer vboSize;
	vboSize.setTarget(gl::VertexBufferTarget::Array);
	vboSize.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboSize.setType(gl::Type::Float);
	vboSize.create();
	vboSize.bind();
	vboSize.addVertexAttrib(2,1,false,1,(const GLvoid*)0);
	vboSize.setData(sizeof(size),size);
	vboSize.unbind();

	vao.unbind();

	printf("vao=%i, vboPos=%i, shader=%i\n",vao.id,vboPos.id,shader.id);

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(.5+.5*cos(gl::time()));
		gl::clearScreen();
		gl::defaultViewport(window);

		shader.bind();
		vao.bind();
		glDrawArrays(GL_POINTS,0,n);
		vao.unbind();
		shader.unbind();

		window.unbind();
	}

	gl::end();

	return 0;
}



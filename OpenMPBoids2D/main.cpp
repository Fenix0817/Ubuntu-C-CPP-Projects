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
#include <glm/glm.hpp>
#include "Boid.h"
#include <omp.h>

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
	window.setSize(1000,1000);

	window.bind();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/boid.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/boid.frag",gl::ShaderType::Fragment);
	shader.attachFile("Shaders/boid.geom",gl::ShaderType::Geometry);
	shader.link();

	int n=600;
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
//		size[i]=0.05+0.1*((float)rand())/((float)RAND_MAX);
		size[i]=0.03;
	}
	float dir[n*2];
	for(int i=0;i<n;i++){
		dir[i*2+0]=0;
		dir[i*2+1]=0;
	}

	Boid boids[n];

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

	gl::VertexBuffer vboDir;
	vboDir.setTarget(gl::VertexBufferTarget::Array);
	vboDir.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboDir.setType(gl::Type::Float);
	vboDir.create();
	vboDir.bind();
	vboDir.addVertexAttrib(3,2,false,2,(const GLvoid*)0);
	vboDir.setData(sizeof(dir),dir);
	vboDir.unbind();

	vao.unbind();

	printf("vao=%i, vboPos=%i, shader=%i\n",vao.id,vboPos.id,shader.id);

	while(window.isOpen()){
		window.bind();

		gl::setClearColor(1);
		gl::clearScreen();
		gl::defaultViewport(window);

		shader.bind();
		vao.bind();

		vboPos.bind();
		float*ptrPos=(float*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		for(int i=0;i<n;i++){
			ptrPos[i*2+0]=boids[i].pos.x;
			ptrPos[i*2+1]=boids[i].pos.y;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vboPos.unbind();

		vboDir.bind();
		float*ptrDir=(float*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		for(int i=0;i<n;i++){
			ptrDir[i*2+0]=boids[i].vel.x;
			ptrDir[i*2+1]=boids[i].vel.y;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vboDir.unbind();

		glDrawArrays(GL_POINTS,0,n);
		vao.unbind();
		shader.unbind();

#pragma omp parallel for
		for(int i=0;i<n;i++){
			boids[i].update(boids,n,i);
		}

		window.unbind();
	}

	gl::end();

	return 0;
}



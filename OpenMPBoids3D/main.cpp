/*
 * main.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Boid.h"
#include <cmath>

inline glm::vec3 lerp(float t,glm::vec3 a,glm::vec3 b){
	return a+(b-a)*t;
}

inline bool isnan3(glm::vec3 v){
	return __builtin_isnan(v.x)||__builtin_isnan(v.y)||__builtin_isnan(v.z);
}

int main(){
	//TODO:  Add shading
	//TODO:  For shading, have a common shader.frag file:
	//	in vec3 color;
	//	in vec3 normal;
	//	in light[] lights;
	//	void main() {
	//		shade();
	//	}
	//TODO:  Look at the OpenGL Cookbook for this
	//TODO:  Shading for boids AND bounds
	srand(time(NULL));

	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("OpenMP 3D Boids");
	window.setSize(500,500);

	window.bind();

	gl::Shader shaderBoids;
	shaderBoids.create();
	shaderBoids.attachFile("Shaders/boid.vert",gl::ShaderType::Vertex);
	shaderBoids.attachFile("Shaders/boid.frag",gl::ShaderType::Fragment);
	shaderBoids.attachFile("Shaders/boid.geom",gl::ShaderType::Geometry);
	shaderBoids.link();

	int n=700;
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
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPos.setData(sizeof(float)*3*n,malloc(sizeof(float)*3*n));
	vboPos.unbind();

	gl::VertexBuffer vboCol;
	vboCol.setTarget(gl::VertexBufferTarget::Array);
	vboCol.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboCol.setType(gl::Type::Float);
	vboCol.create();
	vboCol.bind();
	vboCol.addVertexAttrib(1,3,false,3,(const GLvoid*)0);
	vboCol.setData(sizeof(float)*3*n,malloc(sizeof(float)*3*n));
	vboCol.unbind();

	gl::VertexBuffer vboSize;
	vboSize.setTarget(gl::VertexBufferTarget::Array);
	vboSize.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboSize.setType(gl::Type::Float);
	vboSize.create();
	vboSize.bind();
	vboSize.addVertexAttrib(2,1,false,1,(const GLvoid*)0);
	vboSize.setData(sizeof(float)*n,malloc(sizeof(float)*n));
	vboSize.unbind();

	gl::VertexBuffer vboDir;
	vboDir.setTarget(gl::VertexBufferTarget::Array);
	vboDir.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboDir.setType(gl::Type::Float);
	vboDir.create();
	vboDir.bind();
	vboDir.addVertexAttrib(3,3,false,3,(const GLvoid*)0);
	vboDir.setData(sizeof(float)*3*n,malloc(sizeof(float)*3*n));
	vboDir.unbind();

	vao.unbind();

	float posBounds[]={
			-30,-30,-30,
			 30,-30,-30,
			-30, 30,-30,
			 30, 30,-30,

			-30,-30, 30,
			 30,-30, 30,
			-30, 30, 30,
			 30, 30, 30,
	};

	unsigned int triBounds[]={
			0,1,2, 1,2,3,
			4,5,6, 5,6,7
	};

	gl::Shader shaderBounds;
	shaderBounds.create();
	shaderBounds.attachFile("Shaders/bounds.vert",gl::ShaderType::Vertex);
	shaderBounds.attachFile("Shaders/bounds.frag",gl::ShaderType::Fragment);
	shaderBounds.link();

	gl::VertexArray vaoBounds;
	vaoBounds.create();
	vaoBounds.bind();

	gl::VertexBuffer vboPosBounds;
	vboPosBounds.setTarget(gl::VertexBufferTarget::Array);
	vboPosBounds.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPosBounds.setType(gl::Type::Float);
	vboPosBounds.create();
	vboPosBounds.bind();
	vboPosBounds.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPosBounds.setData(sizeof(posBounds),posBounds);
	vboPosBounds.unbind();

	gl::VertexBuffer eboBounds;
	eboBounds.setTarget(gl::VertexBufferTarget::ElementArray);
	eboBounds.setUsage(gl::VertexBufferUsage::StaticDraw);
	eboBounds.setType(gl::Type::UnsignedInt);
	eboBounds.create();
	eboBounds.bind();
	eboBounds.setData(sizeof(triBounds),triBounds);
	eboBounds.unbind();

//	glm::vec3 camPos(2,1,2);
//	glm::vec3 camLook(0,0,0);
//	float lerpSpeed=0.00000001;

	glm::vec3 positions[n];
	for(int i=0;i<n;i++){
		positions[i]=boids[i].pos;
	}

	while(window.isOpen()){
		window.bind();
		window.updateSize();

		gl::setClearColor(0.3f);
		gl::clearScreen();
		gl::defaultViewport(window);
		gl::setDepth(true);

		glCullFace(GL_NONE);

		glm::mat4 perspective=glm::perspective(glm::radians(80.0f),((float)window.width)/((float)window.height),0.01f,200.0f);
//		float rot=0;
//		float rot=gl::time();
		glm::mat4 view=glm::lookAt(glm::vec3(1,0.5,1),glm::vec3(0,0,0),glm::vec3(0,1,0));
//		Boid boid=boids[0];
//		glm::vec3 dir=glm::normalize(boid.vel);
//		glm::vec3 targetPos=boid.pos-dir*0.2f;
//		glm::vec3 targetLook=boid.pos+dir;
////		camPos=lerp(lerpSpeed,camPos,targetPos);
////		camLook=lerp(lerpSpeed,camLook,targetLook);
//		if(!__builtin_isnan(targetPos.x)&&!__builtin_isnan(targetPos.y)&&!__builtin_isnan(targetPos.z)&&!__builtin_isnan(targetLook.x)&&!__builtin_isnan(targetLook.y)&&!__builtin_isnan(targetLook.z)){
//			camPos+=(targetPos-camPos)*lerpSpeed;
//			camLook+=(targetLook-camLook)*lerpSpeed;
//		}
//		glm::mat4 view=glm::lookAt( targetPos,targetLook,glm::vec3(0,1,0)  );

		shaderBoids.bind();
		shaderBoids.setMat4("perspective",perspective);
		shaderBoids.setMat4("view",view);
		vao.bind();

		vboPos.bind();
		float*ptrPos=(float*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		for(int i=0;i<n;i++){
			ptrPos[i*3+0]=positions[i].x;
			ptrPos[i*3+1]=positions[i].y;
			ptrPos[i*3+2]=positions[i].z;
			if(!isnan3(boids[i].pos))positions[i]=boids[i].pos;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vboPos.unbind();

		vboCol.bind();
		float*ptrCol=(float*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		for(int i=0;i<n;i++){
			ptrCol[i*3+0]=0;
			ptrCol[i*3+1]=0;
			ptrCol[i*3+2]=0;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vboCol.unbind();

		vboSize.bind();
		float*ptrSize=(float*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		for(int i=0;i<n;i++){
			ptrSize[i]=0.02;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		vboSize.unbind();

		glDrawArrays(GL_POINTS,0,n);
		vao.unbind();
		shaderBoids.unbind();


//		shaderBounds.bind();
//		shaderBounds.setMat4("perspective",perspective);
//		shaderBounds.setMat4("view",view);
//		vaoBounds.bind();
//		eboBounds.bind();
//		eboBounds.render();
//		eboBounds.unbind();
//		vaoBounds.unbind();
//		shaderBounds.unbind();

#pragma omp parallel for
		for(int i=0;i<n;i++){
			boids[i].update(boids,n,i);
		}

		window.unbind();
	}

	gl::end();

	return 0;
}




/*
 * main.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdio.h>
#include "Chunk.h"
#define PI 3.14159265359

gl::VertexBuffer createStaticArrayFloatBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Float);
	vbo.create();
	return vbo;
}

gl::VertexBuffer createStaticArrayIntBuffer(){
	gl::VertexBuffer vbo;
	vbo.setTarget(gl::VertexBufferTarget::Array);
	vbo.setUsage(gl::VertexBufferUsage::StaticDraw);
	vbo.setType(gl::Type::Int);
	vbo.create();
	return vbo;
}

float lerp(float t,float a,float b){return a+(b-a)*t;}
float norm(float t,float a,float b){return (t-a)/(b-a);}
float map(float t,float s1,float e1,float s2,float e2){return lerp(norm(t,s1,e1),s2,e2);}

int main(){
	gl::init();

	gl::Window window;
	window.create();
	window.setTitle("YAGL Minecraft");
	window.setSize(1000,1000);
	window.bind();

//	int s=50;
//#define get_ind(x,y,z) ((x)*s*s+(y)*s+(z))
//	float posData[s][s][s][3];
//	int xmiData[s][s][s];
//	int xplData[s][s][s];
//	int ymiData[s][s][s];
//	int yplData[s][s][s];
//	int zmiData[s][s][s];
//	int zplData[s][s][s];
//
//	for(int x=0;x<s;x++){
//		for(int y=0;y<s;y++){
//			for(int z=0;z<s;z++){
//				xmiData[x][y][z]=xplData[x][y][z]=ymiData[x][y][z]=yplData[x][y][z]=zmiData[x][y][z]=zplData[x][y][z]=false;
//				posData[x][y][z][0]=x;
//				posData[x][y][z][1]=y;
//				posData[x][y][z][2]=z;
//			}
//		}
//	}
//
//	bool blocks[s][s][s];
//	for(int x=0;x<s;x++){
//		for(int y=0;y<s;y++){
//			for(int z=0;z<s;z++){
//				blocks[x][y][z]=sqrt(pow(x-s/2,2)+pow(z-s/2,2))>y;
//			}
//		}
//	}
//
//	for(int x=0;x<s;x++){
//		for(int y=0;y<s;y++){
//			for(int z=0;z<s;z++){
//				if(blocks[x][y][z]){
//					if(x>0)if(!blocks[x-1][y][z])xmiData[x][y][z]=true;
//					if(x<s-1)if(!blocks[x+1][y][z])xplData[x][y][z]=true;
//					if(y>0)if(!blocks[x][y-1][z])ymiData[x][y][z]=true;
//					if(y<s-1)if(!blocks[x][y+1][z])yplData[x][y][z]=true;
//					if(z>0)if(!blocks[x][y][z-1])zmiData[x][y][z]=true;
//					if(z<s-1)if(!blocks[x][y][z+1])zplData[x][y][z]=true;
//				}
//			}
//		}
//	}
//
//	gl::VertexArray vao;
//	vao.create();
//	vao.bind();
//
//	gl::VertexBuffer vboPos=createStaticArrayFloatBuffer();
//	vboPos.bind();
//	vboPos.setData(sizeof(posData),posData);
//	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
//	vboPos.unbind();
//
//	gl::VertexBuffer vboXMI=createStaticArrayIntBuffer();
//	vboXMI.bind();
//	vboXMI.setData(sizeof(xmiData),xmiData);
//	vboXMI.addVertexAttrib(1,1,false,1,(const GLvoid*)0);
//	vboXMI.unbind();
//
//	gl::VertexBuffer vboXPL=createStaticArrayIntBuffer();
//	vboXPL.bind();
//	vboXPL.setData(sizeof(xplData),xplData);
//	vboXPL.addVertexAttrib(2,1,false,1,(const GLvoid*)0);
//	vboXPL.unbind();
//
//	gl::VertexBuffer vboYMI=createStaticArrayIntBuffer();
//	vboYMI.bind();
//	vboYMI.setData(sizeof(ymiData),ymiData);
//	vboYMI.addVertexAttrib(3,1,false,1,(const GLvoid*)0);
//	vboYMI.unbind();
//
//	gl::VertexBuffer vboYPL=createStaticArrayIntBuffer();
//	vboYPL.bind();
//	vboYPL.setData(sizeof(yplData),yplData);
//	vboYPL.addVertexAttrib(4,1,false,1,(const GLvoid*)0);
//	vboYPL.unbind();
//
//	gl::VertexBuffer vboZMI=createStaticArrayIntBuffer();
//	vboZMI.bind();
//	vboZMI.setData(sizeof(zmiData),zmiData);
//	vboZMI.addVertexAttrib(5,1,false,1,(const GLvoid*)0);
//	vboZMI.unbind();
//
//	gl::VertexBuffer vboZPL=createStaticArrayIntBuffer();
//	vboZPL.bind();
//	vboZPL.setData(sizeof(zplData),zplData);
//	vboZPL.addVertexAttrib(6,1,false,1,(const GLvoid*)0);
//	vboZPL.unbind();
//
//	vao.unbind();

	Chunk chunk;
	chunk.createBuffers();
	for(int x=0;x<C_SIZE;x++){
		for(int y=0;y<C_HEIGHT;y++){
			for(int z=0;z<C_SIZE;z++){
				int h=(x+z)/2;
				if(y<=h)chunk.setBlock(x,y,z,blockGrass);
				else chunk.setBlock(x,y,z,blockEmpty);
			}
		}
	}
	chunk.updateBuffers();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.attachFile("Shaders/shader.geom",gl::ShaderType::Geometry);
	shader.link();

	window.unbind();

	glm::vec3 camPos(20,-20,20);
	glm::vec3 camDir(-1,1,-1);

	float rotZ=0;
	float rotY=0;

	float speed=0.3;

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(1);
		gl::clearScreen();
		gl::setDepth(true);

		glm::mat4 perspectiveMatrix=glm::perspective(80.0f,((float)window.width)/((float)window.height),0.01f,100.0f);
		glm::mat4 viewMatrix=glm::lookAt(camPos,camPos+camDir,glm::vec3(0,1,0));
//		glm::mat4 viewMatrix=glm::lookAt(glm::vec3(5,-2,3),glm::vec3(0,0,0),glm::vec3(0,1,0));

		shader.bind();
		shader.setMat4("perspectiveMatrix",perspectiveMatrix);
		shader.setMat4("viewMatrix",viewMatrix);
//		vao.bind();
////		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//		glDrawArrays(GL_POINTS,0,s*s*s);
////		glDrawArrays(GL_POINTS,0,numBlocks);
////		glDrawArrays(GL_POINTS,0,2);
//		vao.unbind();
		chunk.render();
		shader.unbind();

		if(window.isKeyDown('W'))camPos+=speed*camDir;
		if(window.isKeyDown('S'))camPos-=speed*camDir;

		float dRZ=map(window.getMouse().y-window.height/2,-300,300,PI/2,-PI/2);
		float dRY=map(window.getMouse().x-window.width/2,-300,300,-PI,PI);
		rotZ+=dRZ;
		rotY+=dRY;

		if(rotZ<-PI/2)rotZ=-PI/2;
		if(rotZ> PI/2)rotZ= PI/2;

		window.setMouse(window.width/2,window.height/2);

		camDir=glm::vec3(1,0,0);
		camDir=glm::rotate(camDir,rotZ,glm::vec3(0,0,1));
		camDir=glm::rotate(camDir,rotY,glm::vec3(0,1,0));

		glm::vec3 camForward=glm::normalize(glm::vec3(camDir.x,0,camDir.z));
		glm::vec3 camRight=glm::vec3(camForward.z,0,-camForward.x);

		if(window.isKeyDown('A'))camPos-=speed*camRight;
		if(window.isKeyDown('D'))camPos+=speed*camRight;

		if(window.isKeyDown('/')||window.isKeyDown(GLFW_KEY_ESCAPE))window.close();
		//  ^  Sometimes ESC key doesn't work on touchbar

		window.updateSize();
		window.unbind();
	}

	gl::end();

	return 0;
}



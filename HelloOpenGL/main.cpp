/*
 * main.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: jack
 */

#include <stdio.h>
#include <cmath>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
//#include <GL/gl.h>


void v(int x,int y,int z){
//	glColor3f(x,y,z);
//	glVertex3f(x,y,z);
}

int main(){
	glfwInit();

	glfwDefaultWindowHints();
	//3.0 and 4.5 work
	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,true);
	GLFWwindow*window=glfwCreateWindow(500,500,"Hello World",nullptr,nullptr);

	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		printf("GLAD not loaded\n");
		return 1;
	}
	const GLubyte*version=glGetString(GL_VERSION);
	const GLubyte*vendor=glGetString(GL_VENDOR);
	const GLubyte*renderer=glGetString(GL_RENDERER);
	int major,minor;
	glGetIntegerv(GL_MAJOR_VERSION,&major);
	glGetIntegerv(GL_MINOR_VERSION,&minor);

	printf("Version: %s\n",version);
	printf("Vendor : %s\n",vendor );
	printf("Renderer: %s\n",renderer);
	printf("Major version: %i\n",major);
	printf("Minor version: %i\n",minor);

	const char*vertSource="#version 450\nlayout (location=0) in vec3 inPos;layout (location=1) in vec3 inCol;out vec3 col;void main(){gl_Position=vec4(inPos,1.0);col=inCol;}";
	const char*fragSource="#version 450\nin vec3 col;out vec4 fc;void main(){fc=vec4(col,1.0);}";
//
	int vert=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert,1,&vertSource,nullptr);
	glCompileShader(vert);
	int success;
	char log[512];
	glGetShaderiv(vert,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(vert,512,nullptr,log);
		printf("VERTEX SHADER\n%s\n",log);
	}

	int frag=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag,1,&fragSource,nullptr);
	glCompileShader(frag);
	glGetShaderiv(frag,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(frag,512,nullptr,log);
		printf("FRAGMENT SHADER\n%s\n",log);
	}

	int prog=glCreateProgram();
	glAttachShader(prog,vert);
	glAttachShader(prog,frag);
	glLinkProgram(prog);

	glDeleteShader(vert);
	glDeleteShader(frag);

	GLuint vao,vboPos,vboCol,ebo;

	float posData[]={
			0,0,0,
			0.9,0,0,
			0,0.9,0,
			0.9,0.9,0,

			-0.9,-0.9,0,
			0,-0.9,0,
			-0.9,0,0,
			0,0,0
	};

	float colData[]={
			1,0,0,
			0,1,0,
			0,0,1,
			1,1,1,

			1,0,0,
			0,1,0,
			0,0,1,
			1,1,1
	};

	GLuint triData[]={
			0,1,3,
			0,2,3,
			4,5,6,
			5,6,7
	};

	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vboPos);
	glGenBuffers(1,&vboCol);
	glGenBuffers(1,&ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vboPos);
	glBufferData(GL_ARRAY_BUFFER,sizeof(posData),posData,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ARRAY_BUFFER,vboCol);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colData),colData,GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(triData),triData,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glBindVertexArray(0);

//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//	glLineWidth(10);
	glEnable(GL_MULTISAMPLE);

	float lastTime,curTime;

	while(!glfwWindowShouldClose(window)){
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);

		lastTime=curTime;
		curTime=glfwGetTime();

		float diff=curTime-lastTime;
		float fps=1.0/diff;

		printf("FPS: %f\n",fps);

		glUseProgram(prog);

		glBindVertexArray(vao);

		float x=0.5*cos(glfwGetTime());
		float y=0;

		posData[0]=x;
		posData[1]=y;

		posData[21]=x;
		posData[22]=y;

		glBindBuffer(GL_ARRAY_BUFFER,vboPos);
		glBufferData(GL_ARRAY_BUFFER,sizeof(posData),posData,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
		glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteProgram(prog);

	glfwTerminate();

	return 0;
}



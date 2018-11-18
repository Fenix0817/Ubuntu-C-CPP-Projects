/*
 * main.cpp
 *
 *  Created on: Oct 27, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Framebuffer.h"

#include "Shader.h"

#include "utils.h"
#include "Pathtracing.h"
#include <vector>


void setMaterial(gl::Shader shader,Material mat,std::string name){
	shader.setVec3(string_format("%s.mat.color",name.c_str()),mat.color);
	shader.setVec3(string_format("%s.mat.light_color",name.c_str()),mat.light_color);
	shader.setFloat(string_format("%s.mat.roughness",name.c_str()),mat.roughness);
}

gl::VertexArray vao;
gl::VertexBuffer vboPos;
gl::VertexBuffer vboUV;
gl::VertexBuffer ebo;

void initBuffers(){
	float posData[]={
			-1,-1,0,
			-1, 1,0,
			 1, 1,0,
			 1,-1,0
	};

	float uvData[]={
			0,0,
			0,1,
			1,1,
			1,0
	};

	unsigned int triData[]={
			0,1,2,
			0,2,3
	};

	vao.create();
	vao.bind();

	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPos.unbind();

	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.addVertexAttrib(1,2,false,2,(const GLvoid*)0);
	vboUV.unbind();

	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();
}

void renderQuad(){
	vao.bind();
	ebo.bind();
	ebo.render();
	ebo.unbind();
	vao.unbind();
}

std::vector<Sphere>spheres;
std::vector<Plane>planes;

void initWorld(){
	Material matte;
	matte.color=glm::vec3(1,1,1);
	matte.light_color=glm::vec3(0,0,0);
	matte.roughness=1;

	Material light;
	light.color=glm::vec3(0,0,0);
	light.light_color=glm::vec3(1,1,1)*1000.0f;
	light.roughness=1;

	for(int i=0;i<5;i++){
		float x=((float)rand())/((float)RAND_MAX);
		float y=((float)rand())/((float)RAND_MAX);
		spheres.push_back(Sphere(glm::vec3(x*10-5,0,y*10-5),1,matte));
	}
	planes.push_back(Plane(glm::vec3(0,0,0),glm::vec3(0,1,0),matte));

	spheres.push_back(Sphere(glm::vec3(0,7,0),3,light));
}

void setWorld(gl::Shader sampleShader,int w,int h,int f){
	sampleShader.setVec2("windowSize",w,h);

	sampleShader.setInt("numSpheres",spheres.size());
	for(int i=0;i<spheres.size();i++){
		sampleShader.setVec3(string_format("spheres[%i].pos",i),spheres[i].pos);
		sampleShader.setFloat(string_format("spheres[%i].rad",i),spheres[i].rad);

		setMaterial(sampleShader,spheres[i].mat,string_format("spheres[%i]",i));
	}

	sampleShader.setInt("numPlanes",planes.size());
	for(int i=0;i<planes.size();i++){
		sampleShader.setVec3(string_format("planes[%i].pos",i),planes[i].pos);
		sampleShader.setVec3(string_format("planes[%i].normal",i),planes[i].normal);

		setMaterial(sampleShader,planes[i].mat,string_format("planes[%i]",i));
	}

	sampleShader.setVec3("background",1,1,1);
	sampleShader.setInt("numFrames",f);

	sampleShader.setVec3("camPos",6,4,3);
	sampleShader.setVec3("lookAt",0,-2,0);
	sampleShader.setFloat("zoom",1);

	sampleShader.setVec3("lightPos",3,2,2);
}

int main(){
	gl::init();

	gl::Window window;
	window.create();
	window.setSize(400,400);
	window.setTitle("YAGL Path Tracing");

	window.bind();

	initBuffers();

	gl::Shader sampleShader;
	sampleShader.create();
	sampleShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	sampleShader.attachFile("Shaders/sample.frag",gl::ShaderType::Fragment);
	sampleShader.link();

	gl::Shader accumShader;
	accumShader.create();
	accumShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	accumShader.attachFile("Shaders/accum.frag",gl::ShaderType::Fragment);
	accumShader.link();

	gl::Shader displayShader;
	displayShader.create();
	displayShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	displayShader.attachFile("Shaders/display.frag",gl::ShaderType::Fragment);
	displayShader.link();

	gl::Texture sampleTexture;
	sampleTexture.setTarget(gl::TextureTarget::Tex2D);
	sampleTexture.create();
	sampleTexture.bind();
	sampleTexture.setData(window.width,window.height,nullptr);
	sampleTexture.unbind();

	gl::Framebuffer sampleFBO;
	sampleFBO.create();
	sampleFBO.bind();
	sampleFBO.attach(sampleTexture,gl::FBOAttachment::Color0);
	if(!sampleFBO.complete())printf("Framebuffer not complete.\n");
	sampleFBO.unbind();


	gl::Texture accumTexture;
	accumTexture.setTarget(gl::TextureTarget::Tex2D);
	accumTexture.create();
	accumTexture.bind();
	accumTexture.setData(window.width,window.height,nullptr);
	accumTexture.unbind();

	gl::Framebuffer accumFBO;
	accumFBO.create();
	accumFBO.bind();
	accumFBO.attach(accumTexture,gl::FBOAttachment::Color0);
	if(!accumFBO.complete())printf("Framebuffer not complete.\n");
	accumFBO.unbind();

	window.unbind();

	initWorld();

	float startTime=gl::time();
	int frames=0;
	int frameCounter=0;
	while(window.isOpen()){
		frames++;
		frameCounter++;
		if(gl::time()-startTime>.3){
			float endTime=gl::time();
			float diffTime=endTime-startTime;

			printf("FPS: %f, SPF: %f\n",frames/diffTime,diffTime/frames);

			frames=0;
			startTime=gl::time();
		}
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(1,1,1);
		gl::clearScreen();

		sampleFBO.bind();
		sampleShader.bind();
		setWorld(sampleShader,window.width,window.height,frameCounter);
		renderQuad();
		sampleShader.unbind();
		sampleFBO.unbind();

		accumFBO.bind();
		accumShader.bind();
		accumShader.setInt("tex1",0);
		sampleTexture.bindToUnit(0);
		accumShader.setInt("tex2",1);
		accumTexture.bindToUnit(1);
		renderQuad();
		accumFBO.unbind();

		displayShader.bind();
		displayShader.setInt("tex",0);
		displayShader.setFloat("colorScale",1);
		accumTexture.bindToUnit(0);
		renderQuad();
		displayShader.unbind();

		window.updateSize();
		window.unbind();
	}

	gl::end();
}

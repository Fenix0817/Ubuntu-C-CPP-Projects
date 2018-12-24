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

#include <stdlib.h>
#include <stdio.h>
//#include <cmath>

#include "tinyxml2.h"

#define IMG_W 500
#define IMG_H 500

#define WINDOW_W 500
#define WINDOW_H 500

void setMaterial(gl::Shader shader,Material mat,std::string name){
	shader.setVec3(string_format("%s.mat.color",name.c_str()),mat.color);
	shader.setVec3(string_format("%s.mat.light_color",name.c_str()),mat.light_color);
	shader.setFloat(string_format("%s.mat.roughness",name.c_str()),mat.roughness);
}

gl::VertexArray vao;
gl::VertexBuffer vboPos;
gl::VertexBuffer vboUV;
gl::VertexBuffer ebo;

glm::vec3 camPos;
glm::vec3 lookAt;
float zoom;

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
std::vector<Disk>disks;

float randomFloat(){
	return ((float)rand())/((float)RAND_MAX);
}

struct NamedMat{
	std::string name;
	Material mat;
};

std::vector<NamedMat>materials;
glm::vec3 background;

void addMaterial(tinyxml2::XMLElement*elem){
	NamedMat m;
	m.name=std::string(elem->Attribute("name"));
	m.mat.roughness=elem->FloatAttribute("roughness",1);
	float c_s=elem->FloatAttribute("color_scale",1);
	m.mat.color.x=elem->FloatAttribute("color_r",1)*c_s;
	m.mat.color.y=elem->FloatAttribute("color_g",1)*c_s;
	m.mat.color.z=elem->FloatAttribute("color_b",1)*c_s;
	float l_c_s=elem->FloatAttribute("light_color_scale",1);
	m.mat.light_color.x=elem->FloatAttribute("light_color_r",0)*l_c_s;
	m.mat.light_color.y=elem->FloatAttribute("light_color_g",0)*l_c_s;
	m.mat.light_color.z=elem->FloatAttribute("light_color_b",0)*l_c_s;
	materials.push_back(m);
}

Material findMat(std::string n){
	for(NamedMat m:materials){
		if(m.name==n)return m.mat;
	}
	printf("Material with name %s not found.\n",n.c_str());
	exit(EXIT_FAILURE);
}

void addSphere(tinyxml2::XMLElement*elem){
	Sphere s;
	s.mat=findMat(std::string(elem->Attribute("material")));
	s.pos.x=elem->FloatAttribute("pos_x");
	s.pos.y=elem->FloatAttribute("pos_y");
	s.pos.z=elem->FloatAttribute("pos_z");
	s.rad=elem->FloatAttribute("rad");
	spheres.push_back(s);
}

void addPlane(tinyxml2::XMLElement*elem){
	Plane p;
	p.mat=findMat(std::string(elem->Attribute("material")));
	p.pos.x=elem->FloatAttribute("pos_x");
	p.pos.y=elem->FloatAttribute("pos_y");
	p.pos.z=elem->FloatAttribute("pos_z");
	p.normal.x=elem->FloatAttribute("normal_x");
	p.normal.y=elem->FloatAttribute("normal_y");
	p.normal.z=elem->FloatAttribute("normal_z");
	planes.push_back(p);
}

void addDisk(tinyxml2::XMLElement*elem){
	Disk d;
	d.mat=findMat(std::string(elem->Attribute("material")));
	d.pos.x=elem->FloatAttribute("pos_x");
	d.pos.y=elem->FloatAttribute("pos_y");
	d.pos.z=elem->FloatAttribute("pos_z");
	d.normal.x=elem->FloatAttribute("normal_x");
	d.normal.y=elem->FloatAttribute("normal_y");
	d.normal.z=elem->FloatAttribute("normal_z");
	d.rad=elem->FloatAttribute("rad");
	disks.push_back(d);
}

void setCamera(tinyxml2::XMLElement*elem){
	camPos.x=elem->FloatAttribute("pos_x");
	camPos.y=elem->FloatAttribute("pos_y");
	camPos.z=elem->FloatAttribute("pos_z");
	lookAt.x=elem->FloatAttribute("look_x",elem->FloatAttribute("dir_x")+camPos.x);
	lookAt.y=elem->FloatAttribute("look_y",elem->FloatAttribute("dir_y")+camPos.y);
	lookAt.z=elem->FloatAttribute("look_z",elem->FloatAttribute("dir_z")+camPos.z);
	zoom=elem->FloatAttribute("zoom",1);
}

void setBackground(tinyxml2::XMLElement*elem){
	background.x=elem->FloatAttribute("r",1);
	background.y=elem->FloatAttribute("g",1);
	background.z=elem->FloatAttribute("b",1);
}

void initWorld(){

	using namespace tinyxml2;

	XMLDocument doc;
	doc.LoadFile("world-cornell-box.xml");

	XMLElement*root=doc.RootElement();

	XMLNode*child=root->FirstChild();
	while(child!=nullptr){

		if(child->ToComment()!=nullptr){
			child=child->NextSibling();
			continue;
		}

		XMLElement*elem=child->ToElement();
		std::string elemName(elem->Name());
		if(elemName=="material"){
			addMaterial(elem);
		}
		if(elemName=="sphere"){
			addSphere(elem);
		}
		if(elemName=="plane"){
			addPlane(elem);
		}
		if(elemName=="disk"){
			addDisk(elem);
		}
		if(elemName=="camera"){
			setCamera(elem);
		}
		if(elemName=="background"){
			setBackground(elem);
		}
		child=child->NextSibling();
	}

//	Material light;
//	light.color=glm::vec3(1,1,1);
//	light.light_color=glm::vec3(1,1,1)*10.0f;
//	light.roughness=1;
//
//	for(int i=0;i<10;i++){
//		float x=((float)rand())/((float)RAND_MAX);
//		float y=((float)rand())/((float)RAND_MAX);
//		Material matte;
//		matte.color=glm::vec3(randomFloat(),randomFloat(),randomFloat());
//		matte.color/=fmax(matte.color.x,fmax(matte.color.y,matte.color.z));
//		printf("%f,%f,%f\n",matte.color.x,matte.color.y,matte.color.z);
//		matte.light_color=glm::vec3(0,0,0);
//		matte.roughness=0;
//		float r=randomFloat()*0.25+1.75;
//		spheres.push_back(Sphere(glm::vec3(x*20-10,0,y*20-10),r,matte));
//	}
//	Material ground;
//	ground.color=glm::vec3(1,1,1);
//	ground.light_color=glm::vec3(0,0,0);
//	ground.roughness=1;
//	planes.push_back(Plane(glm::vec3(0,0,0),glm::vec3(0,1,0),ground));
//
//	Material wall;
//	wall.color=glm::vec3(1,1,1);
//	wall.light_color=glm::vec3(0,0,0);
//	wall.roughness=1;
//	planes.push_back(Plane(glm::vec3(-20,0,0),glm::vec3(1,0,0),wall));
//	planes.push_back(Plane(glm::vec3(0,0,-20),glm::vec3(0,0,1),wall));
//
//	spheres.push_back(Sphere(glm::vec3(0,9,0),6,light));

//	Material ground;
//	ground.color=glm::vec3(1,1,1);
//	ground.light_color=glm::vec3(0,0,0);
//	ground.roughness=1;
//	planes.push_back(Plane(glm::vec3(0,0,0),glm::vec3(0,1,0),ground));
//
//	Material light;
//	light.color=glm::vec3(0,0,0);
//	light.light_color=glm::vec3(1,1,1)*10.0f;
//	light.roughness=1;
//	spheres.push_back(Sphere(glm::vec3(0,8,0),4,light));
//
//	Material sphere1;
//	sphere1.color=glm::vec3(1,1,0.5);
//	sphere1.light_color=glm::vec3(0,0,0);
//	sphere1.roughness=0;
//	Material sphere2;
//	sphere2.color=glm::vec3(0.5,0.5,1);
//	sphere2.light_color=glm::vec3(0,0,0);
//	sphere2.roughness=0.5;
//	Material sphere3;
//	sphere3.color=glm::vec3(1,0.5,0.5);
//	sphere3.light_color=glm::vec3(0,0,0);
//	sphere3.roughness=0;
//	spheres.push_back(Sphere(glm::vec3(2,0,-4),4,sphere1));
//	spheres.push_back(Sphere(glm::vec3(-4,0,2),3,sphere2));
//	spheres.push_back(Sphere(glm::vec3(4,0,4),2,sphere3));
}

void setWorld(gl::Shader sampleShader,int f){
	sampleShader.setVec2("windowSize",IMG_W,IMG_H);

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

	sampleShader.setInt("numDisks",disks.size());
	for(int i=0;i<disks.size();i++){
		sampleShader.setVec3(string_format("disks[%i].pos",i),disks[i].pos);
		sampleShader.setVec3(string_format("disks[%i].normal",i),disks[i].normal);
		sampleShader.setFloat(string_format("disks[%i].rad",i),disks[i].rad);

		setMaterial(sampleShader,disks[i].mat,string_format("disks[%i]",i));
	}

	sampleShader.setVec3("background",background);
	sampleShader.setInt("numFrames",f);

	sampleShader.setVec3("camPos",camPos);
	sampleShader.setVec3("lookAt",lookAt);
	sampleShader.setFloat("zoom",zoom);

	sampleShader.setVec3("lightPos",3,2,2);
}

gl::Shader sampleShader;
gl::Shader accumShader;
gl::Shader displayShader;
gl::Texture sampleTexture;
gl::Framebuffer sampleFBO;
gl::Texture accumTextures[2];
gl::Framebuffer accumFBOs[2];

void initGL(){
	sampleShader.create();
	sampleShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	sampleShader.attachFile("Shaders/sample.frag",gl::ShaderType::Fragment);
	sampleShader.link();

	accumShader.create();
	accumShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	accumShader.attachFile("Shaders/accum.frag",gl::ShaderType::Fragment);
	accumShader.link();

	displayShader.create();
	displayShader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	displayShader.attachFile("Shaders/display.frag",gl::ShaderType::Fragment);
	displayShader.link();

	sampleTexture.setTarget(gl::TextureTarget::Tex2D);
	sampleTexture.create();
	sampleTexture.bind();
	sampleTexture.setData(IMG_W,IMG_H,nullptr);
	sampleTexture.unbind();

	sampleFBO.create();
	sampleFBO.bind();
	sampleFBO.attach(sampleTexture,gl::FBOAttachment::Color0);
	if(!sampleFBO.complete())printf("Framebuffer not complete.\n");
	sampleFBO.unbind();


	for(int i=0;i<2;i++){
		accumTextures[i].setTarget(gl::TextureTarget::Tex2D);
		accumTextures[i].create();
		accumTextures[i].bind();
		accumTextures[i].setData(IMG_W,IMG_H,nullptr);
		accumTextures[i].unbind();
	}

	for(int i=0;i<2;i++){
		accumFBOs[i].create();
		accumFBOs[i].bind();
		accumFBOs[i].attach(accumTextures[i],gl::FBOAttachment::Color0);
		if(!accumFBOs[i].complete())printf("Framebuffer not complete.\n");
		accumFBOs[i].unbind();
	}

	sampleFBO.bind();
	gl::setClearColor(0,0,0);
	gl::clearScreen();
	sampleFBO.unbind();

	for(int i=0;i<2;i++){
		accumFBOs[i].bind();
		gl::setClearColor(0,0,0);
		gl::clearScreen();
		accumFBOs[i].unbind();
	}
}

int buffer=0;

int counter=0;

int texDisplayMode=0;

void setLinear(){
	texDisplayMode=0;
}

void setNearest(){
	texDisplayMode=1;
}

void computeIteration(){
	counter++;
	glViewport(0,0,IMG_W,IMG_H);
	sampleFBO.bind();
	sampleShader.bind();
	setWorld(sampleShader,counter);
	renderQuad();
	sampleShader.unbind();
	sampleFBO.unbind();

	// Write to accumTextures[buffer], read from accumTextures[1-buffer]
	accumFBOs[buffer].bind();
	accumShader.bind();

	accumShader.setInt("tex1",0);
	sampleTexture.bindToUnit(0);

	accumShader.setInt("tex2",1);
	accumTextures[1-buffer].bindToUnit(1);

	accumShader.setFloat("n",counter);

	renderQuad();
	accumShader.unbind();
	accumFBOs[buffer].unbind();
	buffer=1-buffer;
}

int main(){
	srand(time(NULL));
	gl::init();

	gl::Window window;
	window.create();
	window.setSize(WINDOW_W,WINDOW_H);
	window.setTitle("YAGL Path Tracing");

	window.bind();
	glfwSwapInterval(0);
	glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_FALSE);
	glClampColorARB(GL_CLAMP_READ_COLOR_ARB, GL_FALSE);
	glClampColorARB(GL_CLAMP_FRAGMENT_COLOR_ARB, GL_FALSE);

	glClampColor(GL_CLAMP_READ_COLOR,GL_FALSE);

	initBuffers();

	initGL();

	gl::setClearColor(1,1,1);
	gl::clearScreen();

	window.unbind();

	initWorld();

	float startTime=gl::time();
	int frames=0;
	int numIters=100000000;
	bool continueCompute=true;
	while(window.isOpen()){
		frames++;
		if(gl::time()-startTime>.3){
			float endTime=gl::time();
			float diffTime=endTime-startTime;

			printf("FPS: %f, SPF: %f, Iterations: %i\n",frames/diffTime,diffTime/frames,counter);

			frames=0;
			startTime=gl::time();
		}
		window.bind();

		gl::setClearColor(1,1,1);
		gl::clearScreen();

//		computeIteration(window.width,window.height);
//
//		if(window.wasJustPressed('1'))computeIteration(window.width,window.height);
//		if(window.wasJustPressed('2'))for(int i=0;i<5;i++)computeIteration(window.width,window.height);
//		if(window.wasJustPressed('3'))for(int i=0;i<20;i++)computeIteration(window.width,window.height);
//		if(window.wasJustPressed('4'))for(int i=0;i<100;i++)computeIteration(window.width,window.height);
//		if(window.wasJustPressed('5'))for(int i=0;i<500;i++)computeIteration(window.width,window.height);
		if(counter<numIters&&continueCompute)computeIteration();

		if(window.isKeyDown('L')){
			setLinear();
		}
		if(window.isKeyDown('N')){
			setNearest();
		}

		if(window.isKeyDown(GLFW_KEY_ESCAPE)||window.isKeyDown(GLFW_KEY_Q))continueCompute=false;

		gl::defaultViewport(window);
		displayShader.bind();
		displayShader.setInt("uvMode",texDisplayMode);
		displayShader.setVec2("size",IMG_W,IMG_H);
		displayShader.setInt("tex",0);
		accumTextures[buffer].bindToUnit(0);
		displayShader.setFloat("n",counter);
		// ^ Always render first accumulation texture, it doesn't matter which
		//   one, because this shader outputs to the window, not a texture
		renderQuad();
		displayShader.unbind();

//		window.updateSize();
		window.clearInputs();
		window.unbind();
	}

	gl::end();
}

/*
 * main.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */


#include "Window.h"
#include "Utilities.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include <vector>
#include "Block.h"
#include "TexturePos.h"
#include "Atlas.h"
#include "AtlasPos.h"
#include "AtlasHD.h"
#include "AtlasLow.h"
#include "AtlasNormal.h"

#include "FastNoise.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

const int SIZE=16;
const int HEIGHT=10;

Block chunk[SIZE][HEIGHT][SIZE];

std::vector<float>posData;
std::vector<float>uvData;
std::vector<unsigned int>triData;

FastNoise noise;

void initChunk(){
	noise.SetNoiseType(FastNoise::Cubic);
	noise.SetInterp(FastNoise::Hermite);
	for(int x=0;x<SIZE;x++){
		for(int z=0;z<SIZE;z++){

//			int h=x;
			int h=(int)(0.5*HEIGHT+HEIGHT*noise.GetSimplex(x*2.0f,z*2.0f));
			printf("%f\n",h);
			for(int y=0;y<HEIGHT;y++){
//				if(y==h)chunk[x][y][z]=blockGrass;
//				else chunk[x][y][z]=blockEmpty;
				if(y<h-10)chunk[x][y][z]=blockStone;
				else if(y<h)chunk[x][y][z]=blockDirt;
				else if(y==h){
					chunk[x][y][z]=blockGrass;
//					int r=rand()%5;
//					if(r==0)chunk[x][y][z]=blockGrass;
//					if(r==1)chunk[x][y][z]=blockDirt;
//					if(r==2)chunk[x][y][z]=blockStone;
//					if(r==3)chunk[x][y][z]=blockSand;
//					if(r==4)chunk[x][y][z]=blockSnow;
				}
				else chunk[x][y][z]=blockEmpty;
			}

		}
	}
}

void addTriangle(unsigned int a,unsigned int b,unsigned int c){
	unsigned int i=posData.size()/3;
	triData.push_back(i+a);
	triData.push_back(i+b);
	triData.push_back(i+c);
}

void addPos(float x,float y,float z){
	posData.push_back(x);
	posData.push_back(16-y);
	posData.push_back(z);
}

void addUV(float u,float v){
	uvData.push_back(u);
	uvData.push_back(v);
}

void addUV(glm::vec2 v){
	addUV(v.x,v.y);
}

void addUV(TexturePos tp,bool flip=false){
	addUV(tp._00);
	if(flip){
		addUV(tp._10);
		addUV(tp._01);
	}else{
		addUV(tp._01);
		addUV(tp._10);
	}
	addUV(tp._11);
}

void addTriangleFace(){
	addTriangle(0,1,2);
	addTriangle(1,2,3);
}

bool isEmpty(int x,int y,int z){
	if(x<0||y<0||z<0||x>=SIZE||y>=HEIGHT||z>=SIZE)return true;
	return chunk[x][y][z].empty;
}

void initMesh(Atlas*atlas){
	for(int x=0;x<SIZE;x++){
		for(int y=0;y<HEIGHT;y++){
			for(int z=0;z<SIZE;z++){

				Block b=chunk[x][y][z];

				if(b.empty)continue;

				TexturePos xmi=atlas->getTexturePos(b.xmi);
				TexturePos xpl=atlas->getTexturePos(b.xpl);
				TexturePos ymi=atlas->getTexturePos(b.ymi);
				TexturePos ypl=atlas->getTexturePos(b.ypl);
				TexturePos zmi=atlas->getTexturePos(b.zmi);
				TexturePos zpl=atlas->getTexturePos(b.zpl);

				if(isEmpty(x-1,y,z)){//xmi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addUV(xmi);
				}

				if(isEmpty(x+1,y,z)){//xpl
					addTriangleFace();
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addUV(xpl);
				}

				if(isEmpty(x,y-1,z)){//ymi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x+1,y,z);
					addPos(x,y,z+1);
					addPos(x+1,y,z+1);
					addUV(ymi);
				}

				if(isEmpty(x,y+1,z)){//ypl
					addTriangleFace();
					addPos(x,y+1,z);
					addPos(x+1,y+1,z);
					addPos(x,y+1,z+1);
					addPos(x+1,y+1,z+1);
					addUV(ypl);
				}

				if(isEmpty(x,y,z-1)){//zmi
					addTriangleFace();
					addPos(x,y,z);
					addPos(x,y+1,z);
					addPos(x+1,y,z);
					addPos(x+1,y+1,z);
					addUV(zmi);
				}

				if(isEmpty(x,y,z+1)){//zpl
					addTriangleFace();
					addPos(x,y,z+1);
					addPos(x,y+1,z+1);
					addPos(x+1,y,z+1);
					addPos(x+1,y+1,z+1);
					addUV(zpl);
				}

			}
		}
	}
}


int main(){
	gl::init();

	gl::Window window;
//	glfwWindowHint(GLFW_SAMPLES,100);
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Minecraft #1");
	window.setSize(1000,1000);
	window.bind();
//	glEnable(GL_MULTISAMPLE);


//	Atlas* atlas = new AtlasHD();
//	Atlas* atlas = new AtlasLow();
	Atlas* atlas = new AtlasNormal();

//
//	std::vector<float> posData{
//		0,0,0,
//		1,0,0,
//		0,1,0,
//		1,1,0
//	};
//	std::vector<float> uvData={
//		0,0,
//		1,0,
//		0,1,
//		1,1
//	};
//	std::vector<unsigned int> triData={
//			0,1,2,
//			1,2,3
//	};

	initChunk();
	initMesh(atlas);

	gl::VertexArray vao;
	vao.create();
	vao.bind();

	gl::VertexBuffer vboPos(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(float)*posData.size(),posData.data());
	vboPos.addVertexAttrib(0,3,false,3,0);
	vboPos.unbind();

	gl::VertexBuffer vboUV(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(float)*uvData.size(),uvData.data());
	vboUV.addVertexAttrib(1,2,false,2,0);
	vboUV.unbind();

	gl::VertexBuffer ebo(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
	ebo.unbind();

	vao.unbind();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.link();

	gl::Texture texture=gl::loadTexture(atlas->getFileName());

	texture.bind();
	texture.setParam(gl::TextureParamName::MinFilter,gl::TextureParamValue::NearestMipmapLinear);
	texture.setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::NearestMipmapLinear);
	texture.unbind();

	window.unbind();

//	glm::vec3 camPos=glm::vec3(-5,5,-5);
//	glm::vec3 camDir=glm::vec3(1,0,0);

	Camera camera;
	camera.camPos=glm::vec3(-5,5,-5);
	camera.camDir=glm::vec3(1,0,0);

	camera.forwardSpeed=0.2;
	camera.sideSpeed   =0.1;
	camera.backSpeed   =0.025;

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setDepth(true);
		gl::setClearColor(1);
		gl::clearScreen();

		shader.bind();

		texture.bindToUnit(0);
		shader.setInt("tex",0);

		camera.fovy=80;
		camera.windowW=window.width;
		camera.windowH=window.height;

//		glm::mat4 perspective=glm::perspective(80.0f,1.0f*window.width/window.height,0.01f,100.0f);
//		glm::mat4 view=glm::lookAt(glm::vec3(-5*cos(gl::time()),5,-5),glm::vec3(8,16,8),glm::vec3(0,1,0));
//		glm::mat4 view=glm::lookAt(camPos,camPos+camDir,glm::vec3(0,1,0));
//		glm::mat4 model=glm::mat4(1);

		shader.setMat4("MVP",camera.getPerspectiveViewMatrix());

		vao.bind();
		ebo.bind();
		ebo.render();
		ebo.unbind();
		vao.unbind();

		shader.unbind();

//		camDir=glm::vec3(0,0,1);
//		camDir=glm::rotateX(camDir,map(window.getMouse().y,0,window.height,-PI,PI));
//		camDir=glm::rotateY(camDir,map(window.getMouse().x,0,window.width,-PI,PI));

//		glm::vec3 camDirMove=glm::normalize(glm::vec3(camDir.x,0,camDir.z));

//		if(window.isKeyDown('W'))camPos+=0.1f*camDirMove;
//		if(window.isKeyDown('S'))camPos-=0.1f*camDirMove;
//		if(window.isKeyDown('A'))camPos-=0.1f*glm::rotateY(camDirMove,glm::radians(90.0f));
//		if(window.isKeyDown('D'))camPos+=0.1f*glm::rotateY(camDirMove,glm::radians(90.0f));

		camera.updateDirection(window.getMouse());
		glfwSetCursorPos(window.ptr,window.width/2,window.height/2);
		camera.mouse=window.getMouse();

		if(window.isKeyDown('W'))camera.moveForward();
		if(window.isKeyDown('S'))camera.moveBack();
		if(window.isKeyDown('A'))camera.moveLeft();
		if(window.isKeyDown('D'))camera.moveRight();

		if(window.isKeyDown(' '))camera.camPos.y-=0.1;
		if(window.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.camPos.y+=0.1;
		if(window.isKeyDown(GLFW_KEY_ESCAPE))window.close();

		window.clearInputs();
		window.updateSize();
		window.unbind();
	}

	gl::end();
	return 0;
}

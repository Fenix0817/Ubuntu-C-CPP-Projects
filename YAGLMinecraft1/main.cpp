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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SIZE=16;
const int HEIGHT=50;

Block chunk[SIZE][HEIGHT][SIZE];

std::vector<float>posData;
std::vector<float>uvData;
std::vector<unsigned int>triData;

void initChunk(){
	for(int x=0;x<SIZE;x++){
		for(int z=0;z<SIZE;z++){

			int h=x;
			for(int y=0;y<HEIGHT;y++){
//				if(y==h)chunk[x][y][z]=blockGrass;
//				else chunk[x][y][z]=blockEmpty;
				if(y<h-3)chunk[x][y][z]=blockStone;
				else if(y<h)chunk[x][y][z]=blockDirt;
				else if(y==h)chunk[x][y][z]=blockGrass;
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
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Minecraft #1");
	window.setSize(500,500);
	window.bind();

//	Atlas* atlas = new AtlasHD();
	Atlas* atlas = new AtlasLow();

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
//	texture.setParam(gl::TextureParamName::MinFilter,gl::TextureParamValue::Linear);
//	texture.setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::Linear);
	texture.unbind();

	window.unbind();

	while(window.isOpen()){
		window.bind();

		gl::defaultViewport(window);
		gl::setDepth(true);
		gl::setClearColor(1);
		gl::clearScreen();

		shader.bind();

		texture.bindToUnit(0);
		shader.setInt("tex",0);

		glm::mat4 perspective=glm::perspective(80.0f,1.0f,0.01f,100.0f);
		glm::mat4 view=glm::lookAt(glm::vec3(-5*cos(gl::time()),5,-5),glm::vec3(8,16,8),glm::vec3(0,1,0));
		glm::mat4 model=glm::mat4(1);

		shader.setMat4("MVP",perspective*view*model);

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

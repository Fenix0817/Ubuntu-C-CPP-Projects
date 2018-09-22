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
#include "Chunk.h"

#include <utility>

#include "FastNoise.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

bool printError(){
	GLenum e=glGetError();
	switch(e){
	case GL_NO_ERROR: printf("GL_NO_ERROR\n"); return false;
	case GL_INVALID_ENUM: printf("GL_INVALID_ENUM\n"); return true;
	case GL_INVALID_VALUE: printf("GL_INVALID_VALUE\n"); return true;
	case GL_INVALID_OPERATION: printf("GL_INVALID_OPERATION\n"); return true;
	case GL_INVALID_FRAMEBUFFER_OPERATION: printf("GL_INVALID_FRAMEBUFFER_OPERATION\n"); return true;
	case GL_OUT_OF_MEMORY: printf("GL_OUT_OF_MEMORY\n"); return true;
	case GL_STACK_UNDERFLOW: printf("GL_STACK_UNDERFLOW\n"); return true;
	case GL_STACK_OVERFLOW: printf("GL_STACK_OVERFLOW\n"); return true;
	}
	return false;
}

std::vector<ChunkPtr>chunks;

FastNoisePtr noise;

AtlasPtr atlas;

ChunkPtr getChunk(int x,int z,bool instantiateChunk){
	bool foundChunk=false;
	ChunkPtr c=nullptr;
	for(int i=0;i<chunks.size()&&!foundChunk;i++){
		if(chunks[i]->chunkPos.x==x&&chunks[i]->chunkPos.y==z){
			c=chunks[i];
			foundChunk=true;
		}
	}
	if(!foundChunk){
		printf("\tCreating data for %i,%i\n",x,z);
		c=new Chunk();
		c->chunkPos=glm::ivec2(x,z);
		c->createChunkData(noise);
		chunks.push_back(c);
		printf("\tFinished creating data for %i,%i\n",x,z);
	}
	if(instantiateChunk&&!c->instantiated){
		printf("\nInstantiating %i,%i\n",x,z);
		c->instantiated=true;
		ChunkPtr xmi=getChunk(x-1,z,false);
		ChunkPtr xpl=getChunk(x+1,z,false);
		ChunkPtr zmi=getChunk(x,z-1,false);
		ChunkPtr zpl=getChunk(x,z+1,false);
		c->cXMI=xmi;
		c->cXPL=xpl;
		c->cZMI=zmi;
		c->cZPL=zpl;
		c->prepareMesh(atlas);
		c->prepareGL();
		printf("Finished instantiating %i,%i:  %i,%i,%i,%i\n",x,z,c->vao.id,c->vboPos.id,c->vboUV.id,c->ebo.id);
	}
	return c;
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

	atlas=new AtlasNormal();

	noise=new FastNoise();
	noise->SetInterp(FastNoise::Hermite);
	noise->SetCellularReturnType(FastNoise::Distance);
	noise->SetCellularDistanceFunction(FastNoise::Euclidean);

//	for(int x=0;x<5;x++){
//		for(int z=0;z<5;z++){
//			getChunk(x,z,true);
//		}
//	}

	int size=0;
	int realSize=0;
	for(int i=0;i<chunks.size();i++){
		if(chunks[i]->instantiated)realSize++;
		size++;
		printf("Chunk pos %i: %i,%i\n",i,chunks[i]->chunkPos.x,chunks[i]->chunkPos.y);
	}
	printf("%i,%i\n",size,realSize);

	for(int x=-10;x<=10;x++){
		for(int z=-10;z<=10;z++){
			for(int i=0;i<chunks.size();i++){
				if(chunks[i]->chunkPos==glm::ivec2(x,z))printf("has chunk %i,%i\n",x,z);
			}
		}
	}

//
//	Chunk* chunk=new Chunk();
//	printf("Init\n");
//	chunk->createChunkData(noise);
//	printf("Gen\n");
//	Chunk* xmi=emptyChunk();
//	Chunk* xpl=emptyChunk();
//	Chunk* zmi=emptyChunk();
//	Chunk* zpl=emptyChunk();
//	chunk->cXMI=xmi;
//	chunk->cXPL=xpl;
//	chunk->cZMI=zmi;
//	chunk->cZPL=zpl;
//	chunk->prepareMesh(atlas);
//	printf("Mesh created\n");
//	chunk->prepareGL();
//	printf("GL created\n");

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.link();

	gl::Texture texture=gl::loadTexture(atlas->getFileName());

	texture.bind();
	texture.setParam(gl::TextureParamName::MinFilter,gl::TextureParamValue::NearestMipmapLinear);

	printError();
	texture.setParam(gl::TextureParamName::MagFilter,gl::TextureParamValue::NearestMipmapLinear);
	printError();

	texture.unbind();

	window.unbind();

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

		shader.setMat4("MVP",camera.getPerspectiveViewMatrix());
//		shader.setMat4("MVP",camera.getPerspectiveViewMatrix()*chunk->getModelMatrix());
//
//		chunk->render();
		for(int i=0;i<chunks.size();i++){
			ChunkPtr c=chunks[i];
			if(c->instantiated){
				shader.setMat4("MVP",camera.getPerspectiveViewMatrix()*c->getModelMatrix());
				c->render();
			}
		}

		shader.unbind();

		int chunkX=(int)(camera.camPos.x/CHUNK_SIZE);
		int chunkZ=(int)(camera.camPos.z/CHUNK_SIZE);

		for(int x=-2;x<=2;x++){
			for(int z=-2;z<=2;z++){
				getChunk(x+chunkX,z+chunkZ,true);
			}
		}

		//TODO:
		// (1) Implement side-by-side chunk meshing
		// (2) AtlasFogleman: https://github.com/fogleman/Craft/blob/master/textures/texture.png
		// (3) Queue of chunks to add, 1 to 2 per frame
		// (4) Queue of chunks to remove, 1 to 2 per frame

		camera.updateDirection(window.getMouse());
		glfwSetCursorPos(window.ptr,window.width/2,window.height/2);
		camera.mouse=window.getMouse();

		if(window.isKeyDown('W'))camera.moveForward();
		if(window.isKeyDown('S'))camera.moveBack();
		if(window.isKeyDown('A'))camera.moveLeft();
		if(window.isKeyDown('D'))camera.moveRight();

		if(window.isKeyDown(' '))camera.camPos.y-=0.1;
		if(window.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.camPos.y+=0.1;
		if(window.isKeyDown(GLFW_KEY_ESCAPE)||window.isKeyDown('/'))window.close();
		// ABOVE - '/' is a exit key because touchbar sometimes doesn't work

		window.clearInputs();
		window.updateSize();
		window.unbind();
	}

	gl::end();
	return 0;
}

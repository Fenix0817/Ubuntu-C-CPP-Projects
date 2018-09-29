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
#include "AtlasFogleman.h"
#include "Chunk.h"
#include "ChunkManager.h"

#include <utility>

#include "FastNoise.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

//#define DEBUG_FPS
//#define DEBUG_CHUNKMANAGER

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

FastNoisePtr noise;

AtlasPtr atlas;

ChunkManager chunkManager;

int main(){
	//TODO:
	// - Block editing: press ' ' to remove blocks near player
	// - After above, encapsulate game logic
	gl::init();

	gl::Window window;
//	glfwWindowHint(GLFW_SAMPLES,100);
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Minecraft #1");
	window.setSize(1000,1000);
	window.bind();

//	atlas=new AtlasNormal();
//	atlas=new AtlasHD();
	atlas=new AtlasFogleman();

	noise=new FastNoise();

	chunkManager.noise=noise;
	chunkManager.atlas=atlas;

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
	camera.camPos=glm::vec3(CHUNK_SIZE/2,-40,CHUNK_SIZE/2);
	camera.camDir=glm::vec3(1,0,0);

	camera.forwardSpeed=0.1;
	camera.sideSpeed   =0.1;
	camera.backSpeed   =0.1;

	float prevTime=0;
	float time=0;

	int frames=0;

	float fogR=0.7;
	float fogG=0.7;
	float fogB=0.7;

	while(window.isOpen()){
		frames++;
		window.bind();

		prevTime=time;
		time=gl::time();

#ifdef DEBUG_FPS
		printf("SPF: %f, FPS: %f\n",time-prevTime,1/(time-prevTime));
#endif

		gl::defaultViewport(window);
		gl::setDepth(true);
		gl::setClearColor(fogR,fogG,fogB);
		gl::clearScreen();

		shader.bind();
		shader.setVec4("fogColor", fogR,fogG,fogB,1);

		texture.bindToUnit(0);
		shader.setInt("tex",0);

		camera.fovy=80;
		camera.windowW=window.width;
		camera.windowH=window.height;

		chunkManager.render(shader,camera.getPerspectiveViewMatrix());

		shader.unbind();

		glm::vec2 chunkPos=getChunkCoord(glm::ivec2((int)camera.camPos.x,(int)camera.camPos.z));
		chunkManager.update(frames,chunkPos);

		glm::vec2 mouse=window.getMouse();
		camera.updateDirection(mouse);
		if(mouse.x<0||mouse.y<0||mouse.x>window.width||mouse.y>window.height)
				glfwSetCursorPos(window.ptr,window.width/2,window.height/2);
		mouse=window.getMouse();
		camera.mouse=mouse;

		if(window.isKeyDown('W'))camera.moveForward();
		if(window.isKeyDown('S'))camera.moveBack();
		if(window.isKeyDown('A'))camera.moveLeft();
		if(window.isKeyDown('D'))camera.moveRight();

		if(window.isKeyDown(' '))camera.camPos.y-=0.5;
		if(window.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.camPos.y+=0.5;
		if(window.isKeyDown(GLFW_KEY_ESCAPE)||window.isKeyDown('/'))window.close();
		// ABOVE - '/' is a exit key because touchbar ESCAPE sometimes doesn't work

//		if(window.isKeyDown('C')){
		if(true){
			int posX=(int)camera.camPos.x;
			int posY=-(int)camera.camPos.y;
			int posZ=(int)camera.camPos.z;
			int a=2;//Why is this only kind of working?
			printf("start %f\n",camera.camPos.y);
			std::vector<glm::ivec2>changes;
			for(int x=-a;x<=a;x++){
				for(int y=-a;y<=a;y++){
					for(int z=-a;z<=a;z++){
						printf("%i %i %i\n",x,y+(int)camera.camPos.z,z);
						glm::ivec2 worldXZ=glm::ivec2(x+posX,z+posZ);
						glm::ivec2 chunkCoord=getChunkCoord(worldXZ);
						if(!contains_ivec2(changes,chunkCoord))changes.push_back(chunkCoord);
						chunkManager.setBlock(x+posX,y+posY,z+posZ,blockEmpty);
					}
				}
			}
			for(int i=0;i<changes.size();i++){
				printf("\t%i\n",i);
				chunkManager.remeshChunk(changes[i].x,changes[i].y);
			}
		}

		window.clearInputs();
		window.updateSize();
		window.unbind();
	}

	gl::end();
	return 0;
}

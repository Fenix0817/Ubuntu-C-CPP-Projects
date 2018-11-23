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
#include "AtlasMCSimple.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "SelectedBlock.h"
#include "TextAtlas.h"
#include "TextAtlasMonospaced.h"
#include "TextRenderer.h"

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
	glfwSetWindowPos(window.ptr,10,10);
	window.bind();

	TextAtlas*textAtlas=new TextAtlasMonospaced();

	TextRenderer txtRenderer;
	txtRenderer.atlas=textAtlas;
	txtRenderer.init();

//	atlas=new AtlasNormal();
//	atlas=new AtlasHD();
//	atlas=new AtlasFogleman();
	atlas=new AtlasMCSimple();

	noise=new FastNoise();

	chunkManager.noise=noise;
	chunkManager.atlas=atlas;

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/chunk.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/chunk.frag",gl::ShaderType::Fragment);
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
	camera.camPos=glm::vec3(CHUNK_SIZE/2,40,CHUNK_SIZE/2);
	camera.camDir=glm::vec3(1,0,0);

	camera.forwardSpeed=0.5;
	camera.sideSpeed   =0.5;
	camera.backSpeed   =0.5;

	float prevTime=0;
	float time=0;

	int frames=0;

	float fogR=0.7;
	float fogG=0.7;
	float fogB=0.8;

	SelectedBlock selectedBlock;
	selectedBlock.init();

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
		if(window.isKeyDown('F'))camera.fovy=20;
		camera.windowW=window.width;
		camera.windowH=window.height;

		printf("Camera position: %f,%f,%f\nCamera direction: %f,%f,%f\n",camera.camPos.x,camera.camPos.y,camera.camPos.z,camera.camDir.x,camera.camDir.y,camera.camDir.z);

		chunkManager.render(shader,camera.getPerspectiveViewMatrix());

		Intersection selectedIntersection=chunkManager.intersectWorld(camera.camPos,camera.camDir,5000);

		if(selectedIntersection.hit){
			glm::ivec3 s=selectedIntersection.pos;
			printf("Selection hit: %i,%i,%i\n",s.x,s.y,s.z);
			selectedBlock.render(s.x,s.y,s.z,camera);
		}

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

		if(window.isKeyDown(' '))camera.camPos.y+=0.5;
		if(window.isKeyDown(GLFW_KEY_LEFT_SHIFT))camera.camPos.y-=0.5;
		if(window.isKeyDown(GLFW_KEY_ESCAPE)||window.isKeyDown('/'))window.close();
		// ABOVE - '/' is a exit key because touchbar ESCAPE sometimes doesn't work

		if(window.mouseLeftJustPressed){
			chunkManager.setBlock(selectedIntersection.pos.x,selectedIntersection.pos.y,selectedIntersection.pos.z,blockEmpty);
			glm::ivec2 c=getChunkCoord(glm::ivec2(selectedIntersection.pos.x,selectedIntersection.pos.z));
			chunkManager.remeshChunk(c.x,c.y);
			glm::ivec2 p=getPosInChunk(glm::ivec2(selectedIntersection.pos.x,selectedIntersection.pos.z));
			if(p.x==0)chunkManager.remeshChunk(c.x-1,c.y);
			if(p.y==0)chunkManager.remeshChunk(c.x,c.y-1);
			if(p.x==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x+1,c.y);
			if(p.y==CHUNK_SIZE-1)chunkManager.remeshChunk(c.x,c.y+1);
		}

		if(window.isKeyDown('C')&&selectedIntersection.hit){
//		if(true){
//			int posX=(int)camera.camPos.x;
//			int posY=(int)camera.camPos.y;
//			int posZ=(int)camera.camPos.z;
			int posX=(int)selectedIntersection.pos.x;
			int posY=(int)selectedIntersection.pos.y;
			int posZ=(int)selectedIntersection.pos.z;
			int a=4;//Why is this only kind of working?
			printf("start %f\n",camera.camPos.y);
			std::vector<glm::ivec2>changes;
			for(int x=-a;x<=a;x++){
				for(int y=-a;y<=a;y++){
					for(int z=-a;z<=a;z++){
						if(y+posY<0)continue;
						printf("%i %i %i\n",x,y,z);
						glm::ivec2 worldXZ=glm::ivec2(x+posX,z+posZ);
						glm::ivec2 chunkCoord=getChunkCoord(worldXZ);
						if(!contains_ivec2(changes,chunkCoord))changes.push_back(chunkCoord);
						if(!contains_ivec2(changes,chunkCoord+glm::ivec2(-1,0)))changes.push_back(chunkCoord+glm::ivec2(-1,0));
						if(!contains_ivec2(changes,chunkCoord+glm::ivec2( 1,0)))changes.push_back(chunkCoord+glm::ivec2( 1,0));
						if(!contains_ivec2(changes,chunkCoord+glm::ivec2(0,-1)))changes.push_back(chunkCoord+glm::ivec2(0,-1));
						if(!contains_ivec2(changes,chunkCoord+glm::ivec2(0, 1)))changes.push_back(chunkCoord+glm::ivec2(0, 1));
						chunkManager.setBlock(x+posX,y+posY,z+posZ,blockEmpty);
					}
				}
			}
			for(int i=0;i<changes.size();i++){
				printf("\t%i\n",i);
				chunkManager.remeshChunk(changes[i].x,changes[i].y);
			}
		}

		txtRenderer.setText("Hello World");
		txtRenderer.render(-1,1,0.1);

		window.clearInputs();
		window.updateSize();
		window.unbind();
	}

	gl::end();
	return 0;
}

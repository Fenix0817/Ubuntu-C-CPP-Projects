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

#include "Atlas.h"
#include "AtlasFogleman.h"

#include "SimplexNoise.h"

float randomFloat(){
	return ((float)rand())/((float)RAND_MAX);
}

// NEG Y = UP
// POS Y = DOWN

#define PI 3.14159265359

float lerp(float t,float a,float b){return a+(b-a)*t;}
float norm(float t,float a,float b){return (t-a)/(b-a);}
float map(float t,float s1,float e1,float s2,float e2){return lerp(norm(t,s1,e1),s2,e2);}

std::vector<Chunk*>chunks;

Chunk*findChunk(int x,int z){
	for(Chunk*c:chunks){
		if(c->pos.x==x&&c->pos.y==z)return c;
	}
	return new Chunk();
}

int main(){
	gl::init();

	gl::Window window;
	window.create();
	window.setTitle("YAGL Minecraft");
	window.setSize(1000,1000);
	window.bind();

	SimplexNoise*sn=new SimplexNoise();

	Atlas*atlas=new AtlasFogleman();

	int world_cw=5;
	int world_ch=5;

	std::vector<glm::vec2>points;
	for(int i=0;i<5;i++){
		points.push_back(glm::vec2(randomFloat()*world_cw,randomFloat()*world_ch)*(float)C_SIZE);
	}

#define taxicab_dist(a,b) (abs(a.x-b.x)+abs(a.y-b.y))
	for(int cx=0;cx<world_cw;cx++){
		for(int cz=0;cz<world_ch;cz++){
			Chunk*c=new Chunk(cx,cz);
			c->createBuffers();
			for(int x=0;x<C_SIZE;x++){
				for(int y=0;y<C_HEIGHT;y++){
					for(int z=0;z<C_SIZE;z++){
						float rx=cx*C_SIZE+x;
						float rz=cz*C_SIZE+z;

//						glm::vec2 pos(rx,rz);
//						glm::vec2 nearest=points[0];
//
//						for(glm::vec2 p:points){
//							if(taxicab_dist(p,pos)<taxicab_dist(nearest,pos)){
//								nearest=p;
//							}
//						}
//
////						int h=taxicab_dist(pos,nearest);
//						int h=sqrt(pow(x-C_SIZE/2,2)+pow(z-C_SIZE/2,2));
//						int h=sn->noise(rx*0.05,0,rz*0.05)*10+20;

//						if(y==h)c->setBlock(x,y,z,blockGrass);
//						else if(y>h)c->setBlock(x,y,z,blockStone);
//						else c->setBlock(x,y,z,blockEmpty);

						if(sn->noise(rx*0.01,y*0.03,rz*0.03)<0)c->setBlock(x,y,z,blockGrass);
						else c->setBlock(x,y,z,blockEmpty);

					}
				}
			}

			chunks.push_back(c);
		}
	}

	for(Chunk*c:chunks){
		int x=c->pos.x;
		int z=c->pos.y;
		c->updateBuffers(atlas,findChunk(x-1,z),findChunk(x+1,z),findChunk(x,z-1),findChunk(x,z+1));
	}

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.attachFile("Shaders/shader.geom",gl::ShaderType::Geometry);
	shader.link();


	gl::Texture atlasTex=gl::loadTexture(atlas->getFileName());

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

		shader.bind();
		shader.setMat4("perspectiveMatrix",perspectiveMatrix);

		shader.setInt("atlasTex",0);
		atlasTex.bindToUnit(0);

		shader.setVec3("camPos",camPos);
		shader.setVec3("camDir",camDir);

		for(Chunk*c:chunks){
			shader.setMat4("modelViewMatrix",viewMatrix*c->getModelMatrix());
			shader.setVec3("posOffset",c->pos.x*C_SIZE,0,c->pos.y*C_SIZE);
			c->render();
		}
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

		printf("%f,%f,%f   %f,%f,%f\n",camPos.x,camPos.y,camPos.z,camDir.x,camDir.y,camDir.z);

		window.updateSize();
		window.unbind();
	}

	gl::end();

	return 0;
}



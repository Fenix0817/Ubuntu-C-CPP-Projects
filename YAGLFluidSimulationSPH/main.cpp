/*
 * main.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <glm/glm.hpp>

#include <vector>

using glm::vec2;

using std::vector;

struct particle {
	particle() : x(0,0), v(0,0), f(0,0), rho(0), p(0) {}
	particle(float _x,float _y) : x(_x,_y), v(0,0), f(0,0), rho(0), p(0) {}
	vec2 x,v,f;
	float rho,p;
};

const float SIM_W = 1000;
const float SIM_H = 1000;
const int SIM_WI  = (int) SIM_W;
const int SIM_HI  = (int) SIM_H;

const float DISPLAY_SIZE = 25/2+3;


const static vec2 G(0.f, 12000*-9.8f);
const static float REST_DENS = 1000.f;
const static float GAS_CONST = 2000.f;
const static float H = 25.f;
const static float HSQ = H*H;
const static float MASS = 65.f;
const static float VISC = 250.f;
const static float DT = 0.0008f;

const static float POLY6 = 315.f/(65.f*M_PI*pow(H, 9.f));
const static float SPIKY_GRAD = -45.f/(M_PI*pow(H, 6.f));
const static float VISC_LAP = 45.f/(M_PI*pow(H, 6.f));

const static float BOUND_SIZE = H;
const static float BOUND_DAMPING = -0.5f;

vector<particle>list;
vector<float>posData;
vector<float>colData;
vector<unsigned int>triData;

void initSimulation(){
	for(int i=0;i<500;i++){
		float x=rand()%200-100+SIM_WI/2;
		float y=rand()%200-100+SIM_HI/2;
		printf("(%f,%f)\n",x,y);
		list.push_back(particle(x,y));

		posData.push_back(x - DISPLAY_SIZE);posData.push_back(y - DISPLAY_SIZE);
		posData.push_back(x + DISPLAY_SIZE);posData.push_back(y - DISPLAY_SIZE);
		posData.push_back(x - DISPLAY_SIZE);posData.push_back(y + DISPLAY_SIZE);
		posData.push_back(x + DISPLAY_SIZE);posData.push_back(y + DISPLAY_SIZE);

		triData.push_back(i*4+0);
		triData.push_back(i*4+1);
		triData.push_back(i*4+2);
		triData.push_back(i*4+1);
		triData.push_back(i*4+2);
		triData.push_back(i*4+3);

//		colData.insert(colData.end(), {1,0,0,  0,1,0,  0,0,1,  1,1,0});
		colData.push_back(1);colData.push_back(0);colData.push_back(0);
		colData.push_back(0);colData.push_back(1);colData.push_back(0);
		colData.push_back(0);colData.push_back(0);colData.push_back(1);
		colData.push_back(1);colData.push_back(1);colData.push_back(0);
	}

}

void stepSimulation(){

	//density and pressure
	for(unsigned int i=0;i<list.size();i++){
		list[i].rho=0;
		for(unsigned int j=0;j<list.size();j++){
			vec2 rij=list[j].x-list[i].x;
			float r2=rij.x*rij.x+rij.y*rij.y;
			if(r2<HSQ){
				list[i].rho+=MASS*POLY6*pow(HSQ-r2,3);
			}
		}
		list[i].p=GAS_CONST*(list[i].rho-REST_DENS);
	}

	//forces
	for(unsigned int i=0;i<list.size();i++){
		vec2 fpress(0,0);
		vec2 fvisc(0,0);
		for(unsigned int j=0;j<list.size();j++){
			if(i==j)continue;
			vec2 rij=list[j].x-list[i].x;
			float r=glm::length(rij);
			if(r<H){
				fpress+=-glm::normalize(rij)*MASS*(list[i].p+list[j].p)/(2*list[j].rho)*SPIKY_GRAD*(float)pow(H-r,2);
				fvisc+=VISC*MASS*(list[j].v-list[i].v)/list[j].rho*VISC_LAP*(H-r);
			}
		}
		list[i].f=G*list[i].rho+fpress+fvisc;
	}

	//integration
	for(unsigned int i=0;i<list.size();i++){
		list[i].v+=DT*list[i].f/list[i].rho;
		list[i].x+=DT*list[i].v;

		if(list[i].x.x<BOUND_SIZE){
			list[i].x.x=BOUND_SIZE;
			list[i].v.x*=BOUND_DAMPING;
		}

		if(list[i].x.y<BOUND_SIZE){
			list[i].x.y=BOUND_SIZE;
			list[i].v.y*=BOUND_DAMPING;
		}

		if(list[i].x.x>SIM_W-BOUND_SIZE){
			list[i].x.x=SIM_W-BOUND_SIZE;
			list[i].v.x*=BOUND_DAMPING;
		}

		if(list[i].x.y>SIM_H-BOUND_SIZE){
			list[i].x.y=SIM_H-BOUND_SIZE;
			list[i].v.y*=BOUND_DAMPING;
		}
	}

	for(unsigned int i=0;i<list.size();i++){
		float x=list[i].x.x;
		float y=list[i].x.y;
		posData[i*8+0]=x-DISPLAY_SIZE;posData[i*8+1]=y-DISPLAY_SIZE;
		posData[i*8+2]=x+DISPLAY_SIZE;posData[i*8+3]=y-DISPLAY_SIZE;
		posData[i*8+4]=x-DISPLAY_SIZE;posData[i*8+5]=y+DISPLAY_SIZE;
		posData[i*8+6]=x+DISPLAY_SIZE;posData[i*8+7]=y+DISPLAY_SIZE;

		float gray=list[i].rho*30;
		float r=0.2*gray;
		float g=0.6*gray;
		float b=1.0*gray;

		for(int j=0;j<4;j++){
			colData[i*12+j*3+0]=r;
			colData[i*12+j*3+1]=g;
			colData[i*12+j*3+2]=b;
		}
	}

}

int main(){
	gl::init();

	gl::Window window;
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Fluid Simulation: SPH");
	window.setSize(SIM_W,SIM_H);

	window.bind();

	printf("Major version ..... %i\n",gl::majorVersion());
	printf("Minor version ..... %i\n",gl::minorVersion());
	printf("Version ........... %s\n",gl::version());
	printf("Vendor ............ %s\n",gl::vendor());
	printf("Renderer .......... %s\n",gl::renderer());

	initSimulation();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/particle.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/particle.frag",gl::ShaderType::Fragment);
	shader.link();

	gl::VertexArray vao;
	vao.create();
	vao.bind();

//
//	vector<float> posData={
//			0,0,0,
//			1,0,0,
//			0,1,0
//	};
//
//	vector<float> colData={
//			1,0,0,
//			0,1,0,
//			0,0,1
//	};
//
//	vector<unsigned int> triData={
//			0,1,2
//	};

	gl::VertexBuffer vboPos(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
//	vboPos.setTarget(gl::VertexBufferTarget::Array);
//	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
//	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(float)*posData.size(),posData.data());
	vboPos.addVertexAttrib(0,2,false,2,0);
	vboPos.unbind();

	gl::VertexBuffer vboCol(gl::VertexBufferTarget::Array,gl::VertexBufferUsage::StaticDraw,gl::Type::Float);
//	vboCol.setTarget(gl::VertexBufferTarget::Array);
//	vboCol.setUsage(gl::VertexBufferUsage::StaticDraw);
//	vboCol.setType(gl::Type::Float);
	vboCol.create();
	vboCol.bind();
	vboCol.setData(sizeof(float)*colData.size(),colData.data());
	vboCol.addVertexAttrib(1,3,false,3,0);
	vboCol.unbind();

	gl::VertexBuffer ebo(gl::VertexBufferTarget::ElementArray,gl::VertexBufferUsage::StaticDraw,gl::Type::UnsignedInt);
//	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
//	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
//	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(unsigned int)*triData.size(),triData.data());
	ebo.unbind();

	vao.unbind();

	window.unbind();

	//TODO: add mouse interactivity to gl::Window and this

	vec2 lastMousePos(0,0);
	vec2 mousePos(0,0);

	while(window.isOpen()){
		window.bind();

		lastMousePos=mousePos;
		mousePos=window.getMouse();

		vec2 diff=mousePos-lastMousePos;

		for(unsigned int i=0;i<list.size();i++){
			if(glm::length(mousePos-list[i].x)<150){
				list[i].v+=30.0f*diff;
			}
		}

		gl::setClearColor(1);
		gl::clearScreen();
		gl::defaultViewport(window);

		stepSimulation();

		shader.bind();

		shader.setVec2("size",SIM_W,SIM_H);

			vao.bind();

				vboPos.bind();
				vboPos.setData(sizeof(float)*posData.size(),posData.data());
				vboPos.unbind();

				vboCol.bind();
				vboCol.setData(sizeof(float)*colData.size(),colData.data());
				vboCol.unbind();

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

/*
 * Boid.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#include "Boid.h"

//Params params;

#define randPos (((float)rand())/((float)RAND_MAX))

Boid::Boid() {
	// TODO Auto-generated constructor stub
	pos=(2.0f*glm::vec3(randPos,randPos,randPos)-1.0f)*0.5f;
	vel=glm::vec3(0,0,0);
}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

void Boid::update(Boid*boids,int n,int selfI){
	lastPos=pos;
	float viewDist=0.1;
	float maxVel=0.005;
	float sepDist=0.04;
	float bounds=0.75;
	float bDamp=0.1;
	float dt=1.0f;
	glm::vec3 com(0,0,0);
	int com_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		com_n++;
		com+=boids[i].pos-pos;
	}
	if(com_n!=0)com/=com_n;

	glm::vec3 rule1=(com)*0.001f;

	glm::vec3 sep(0,0,0);
	int sep_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>sepDist)continue;
		sep_n++;
		sep+=pos-boids[i].pos;
	}
	if(sep_n!=0)sep/=sep_n;

	glm::vec3 rule2=sep*0.02f;

	glm::vec3 cov(0,0,0);
	int cov_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		cov_n++;
		cov+=boids[i].vel;
	}
	if(cov_n!=0)cov/=cov_n;

	glm::vec3 rule3=cov*0.05f;

	glm::vec3 acc=rule1+rule2+rule3;
//	if(selfI==0){
//		printf("vel=%f,%f,%f  acc=%f,%f,%f\n",vel.x,vel.y,vel.z,acc.x,acc.y,acc.z);
//		printf("rule1=%f,%f,%f  rule2=%f,%f,%f  rule3=%f,%f,%f\n",rule1.x,rule1.y,rule1.z,rule2.x,rule2.y,rule2.z,rule3.x,rule3.y,rule3.z);
//		printf("com_n=%i  sep_n=%i  cov_n=%i\n",com_n,sep_n,cov_n);
//	}

	vel+=acc*dt;
	if(glm::length(vel)>maxVel)vel=maxVel*glm::normalize(vel);
	pos+=vel*dt;

	//add boundary conditions
	if(pos.x<-bounds)vel.x += abs(vel.x)*bDamp;
	if(pos.y<-bounds)vel.y += abs(vel.y)*bDamp;
	if(pos.z<-bounds)vel.z += abs(vel.z)*bDamp;
	if(pos.x> bounds)vel.x +=-abs(vel.x)*bDamp;
	if(pos.y> bounds)vel.y +=-abs(vel.y)*bDamp;
	if(pos.z> bounds)vel.z +=-abs(vel.z)*bDamp;
}

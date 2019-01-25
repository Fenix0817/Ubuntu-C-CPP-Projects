/*
 * Boid.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#include "Boid.h"

//Params params;

Boid::Boid() {
	// TODO Auto-generated constructor stub
	pos=1.6f*glm::vec2(((float)rand())/((float)RAND_MAX),((float)rand())/((float)RAND_MAX))-0.8f;
	vel=glm::vec2(0,0);
	acc=glm::vec2(0,0);
}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

void Boid::update(Boid*boids,int n,int selfI){
	float viewDist=0.1;
	float maxVel=0.005;
	float sepDist=0.04;
	float bounds=0.75;
	float bDamp=0.1;

	glm::vec2 com(0,0);
	int com_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		com_n++;
		com+=boids[i].pos-pos;
	}
	if(com_n!=0)com/=com_n;

	glm::vec2 rule1=(com)*0.001f;

	glm::vec2 sep(0,0);
	int sep_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>sepDist)continue;
		sep_n++;
		sep+=pos-boids[i].pos;
	}
	if(sep_n!=0)sep/=sep_n;

	glm::vec2 rule2=sep*0.02f;

	glm::vec2 cov(0,0);
	int cov_n=0;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		cov_n++;
		cov+=boids[i].vel;
	}
	if(cov_n!=0)cov/=cov_n;

	glm::vec2 rule3=cov*0.05f;

	vel+=rule1;
	vel+=rule2;
	vel+=rule3;
	if(glm::length(vel)>maxVel)vel=maxVel*glm::normalize(vel);
	pos+=vel;

	//add boundary conditions
	if(pos.x<-bounds)vel.x += abs(vel.x)*bDamp;
	if(pos.y<-bounds)vel.y += abs(vel.y)*bDamp;
	if(pos.x> bounds)vel.x +=-abs(vel.x)*bDamp;
	if(pos.y> bounds)vel.y +=-abs(vel.y)*bDamp;
}

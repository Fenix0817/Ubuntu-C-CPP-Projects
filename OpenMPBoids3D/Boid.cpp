/*
 * Boid.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: jack
 */

#include "Boid.h"

Boid::Boid() {
	// TODO Auto-generated constructor stub
	pos=glm::vec3(rand(-10,10),rand(-10,10),rand(-10,10));
	vel=glm::vec3(0,0,0);
	acc=glm::vec3(0,0,0);
}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

void Boid::update(Boid*boids,int n,int selfI){
	float viewDist=20;
	float maxVel=0.1;
	float sepDist=2;
	float sepFactor=0.01f;
	float comFactor=0.001f;
	float covFactor=0.1f;
	float bounds=30;
	float bDamp=0.1;

	glm::vec3 com(0,0,0);
	int com_n=0;
#ifdef USE_OMP
#pragma omp parallel for
#endif
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		com_n++;
		com+=boids[i].pos-pos;
	}
	if(com_n!=0)com/=com_n;

	glm::vec3 rule1=com*comFactor;

	glm::vec3 sep(0,0,0);
	int sep_n=0;
#ifdef USE_OMP
#pragma omp parallel for
#endif
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>sepDist)continue;
		sep_n++;
		sep+=pos-boids[i].pos;
	}
	if(sep_n!=0)sep/=sep_n;

	glm::vec3 rule2=sep*sepFactor;

	glm::vec3 cov(0,0,0);
	int cov_n=0;
#ifdef USE_OMP
#pragma omp parallel for
#endif
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>viewDist)continue;
		cov_n++;
		cov+=boids[i].vel;
	}
	if(cov_n!=0)cov/=cov_n;

	glm::vec3 rule3=cov*covFactor;

	vel+=rule1;
	vel+=rule2;
	vel+=rule3;
	if(glm::length(vel)>maxVel)vel=maxVel*glm::normalize(vel);
	pos+=vel;

	//add boundary conditions
	if(pos.x<-bounds)vel.x= abs(vel.x)*bDamp;
	if(pos.y<-bounds)vel.y= abs(vel.y)*bDamp;
	if(pos.z<-bounds)vel.z= abs(vel.z)*bDamp;
	if(pos.x> bounds)vel.x=-abs(vel.x)*bDamp;
	if(pos.y> bounds)vel.y=-abs(vel.y)*bDamp;
	if(pos.z> bounds)vel.z=-abs(vel.z)*bDamp;
}

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
	pos=2.0f*glm::vec2(((float)rand())/((float)RAND_MAX),((float)rand())/((float)RAND_MAX))-1.0f;
	vel=glm::vec2(0,0);
	acc=glm::vec2(0,0);
	params=nullptr;
}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

void Boid::update(Boid*boids,int n,int selfI){
	glm::vec2 centerOfMass(0,0);
	int com_n=0;

#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>params->viewDist)continue;
		if(glm::length(boids[i].pos-pos)<params->sepDist*2)continue;
		com_n++;
		centerOfMass+=boids[i].pos;
	}
	if(com_n!=0)centerOfMass/=com_n;

	glm::vec2 sep(0,0);

#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)<params->sepDist){
			sep+=boids[i].pos-pos;
		}
	}
	sep/=n-1;

	glm::vec2 centerOfVel(0,0);
	int cov_n=0;

#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(i==selfI)continue;
		if(glm::length(boids[i].pos-pos)>params->viewDist)continue;
		if(glm::length(boids[i].pos-pos)<params->sepDist*2)continue;
		cov_n++;
		centerOfVel+=boids[i].vel;
	}
	if(cov_n!=0)centerOfVel/=cov_n;

	acc=glm::vec2(0,0);

	acc+=(centerOfMass-pos)*params->centerOfMassAttraction;
	acc-=sep*params->seperation;
	acc+=centerOfVel*params->centerOfVelAttraction;

	vel+=acc*params->dt;
	vel*=params->velDamping;
	pos+=vel*params->dt;

	if(pos.x<-.8)vel.x=abs(vel.x);
	if(pos.y<-.8)vel.y=abs(vel.y);
	if(pos.x> .8)vel.x=-abs(vel.x);
	if(pos.y> .8)vel.y=-abs(vel.y);
}

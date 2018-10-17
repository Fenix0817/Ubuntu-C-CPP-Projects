/*
 * Boid.h
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#ifndef BOID_H_
#define BOID_H_

#include <glm/glm.hpp>
#include <stdio.h>
#include <stddef.h>

struct Params {
	Params(){dt=0;centerOfMassAttraction=0;seperation=0;velDamping=0;centerOfVelAttraction=0;sepDist=0;viewDist=0;}
	float dt;
	float centerOfMassAttraction;
	float centerOfVelAttraction;
	float seperation;
	float velDamping;
	float viewDist;
	float sepDist;
};

class Boid;

class Boid {
public:
	Boid();
	virtual ~Boid();

	Params*params;

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;

	void update(Boid*boids,int n,int selfI);
};

#endif /* BOID_H_ */

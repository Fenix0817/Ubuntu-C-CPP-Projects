/*
 * Boid.h
 *
 *  Created on: Oct 17, 2018
 *      Author: jack
 */

#ifndef BOID_H_
#define BOID_H_

#include <glm/glm.hpp>
#include <stdio.h>

class Boid;

inline float rand(float mi,float ma){
	return mi+(ma-mi)*((float)rand())/((float)RAND_MAX);
}

class Boid {
public:
	Boid();
	virtual ~Boid();

	glm::vec3 pos;
	glm::vec3 vel;

	glm::vec3 lastPos;

	void update(Boid*boids,int n,int selfI);
};

#endif /* BOID_H_ */

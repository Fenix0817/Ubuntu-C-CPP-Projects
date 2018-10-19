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

class Boid;

class Boid {
public:
	Boid();
	virtual ~Boid();

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;

	void update(Boid*boids,int n,int selfI);
};

#endif /* BOID_H_ */

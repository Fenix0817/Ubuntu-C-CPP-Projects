/*
 * Tracer.h
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#ifndef TRACER_H_
#define TRACER_H_

#include "utils.h"
#include "Ray.h"
#include "World.h"

class Tracer {
public:
	Tracer();
	virtual ~Tracer();

	World*world;

	virtual void create() = 0;
	virtual RGBColor traceRay(Ray&ray) = 0;
};

#endif /* TRACER_H_ */

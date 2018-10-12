/*
 * TracerSphereSampling.h
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#ifndef TRACERSPHERESAMPLING_H_
#define TRACERSPHERESAMPLING_H_

#include "Tracer.h"
	#include "tracerutils.h"
#include "utils.h"
	#include "Colors.h"
#include "Object.h"
	#include "Plane.h"
	#include "Sphere.h"

class TracerSphereSampling : public Tracer {
public:
	TracerSphereSampling();
	virtual ~TracerSphereSampling();

	std::vector<Object*> world;

	void create();
	RGBColor traceRay(Ray&ray);
};

#endif /* TRACERSPHERESAMPLING_H_ */

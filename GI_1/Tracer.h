/*
 * Tracer.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef TRACER_H_
#define TRACER_H_

#include "Math.h"

class Tracer {
public:
	Tracer();
	virtual ~Tracer();

	virtual vec3 getColor(int x,int y)=0;
};

#endif /* TRACER_H_ */

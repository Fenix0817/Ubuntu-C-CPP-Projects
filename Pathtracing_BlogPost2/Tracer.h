/*
 * Tracer.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef TRACER_H_
#define TRACER_H_

#include "Ray.h"
#include "ShadeInfo.h"

class Tracer {
public:
	Tracer();
	virtual ~Tracer();

	virtual RGBColor getColor(Ray ray)=0;
};

#endif /* TRACER_H_ */

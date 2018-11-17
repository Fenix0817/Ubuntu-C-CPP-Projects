/*
 * TracerGI.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef TRACERGI_H_
#define TRACERGI_H_

#include "Tracer.h"
#include "Material.h"
#include "World.h"
#include "TracerUtils.h"
#include "Math.h"

class TracerGI : public Tracer {
public:
	TracerGI();
	virtual ~TracerGI();

	World*world;

	TracerGI(World*w){
		world=w;
	}

	RGBColor getColor(Ray ray){return getColor(ray,0);}
	RGBColor getColor(Ray ray,int depth=0);
};

#endif /* TRACERGI_H_ */

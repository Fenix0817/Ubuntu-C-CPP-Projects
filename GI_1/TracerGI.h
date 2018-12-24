/*
 * TracerGI.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef TRACERGI_H_
#define TRACERGI_H_

#include "Tracer.h"
#include "Camera.h"
#include "ObjectSphere.h"

class TracerGI : public Tracer {
public:
	TracerGI();
	virtual ~TracerGI();

	Camera*camera;

	inline TracerGI(Camera*c){
		this->camera=c;
	}

	vec3 getColor(int x,int y);
};

#endif /* TRACERGI_H_ */

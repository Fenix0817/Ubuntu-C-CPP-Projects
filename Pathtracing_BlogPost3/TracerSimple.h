/*
 * TracerSimple.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef TRACERSIMPLE_H_
#define TRACERSIMPLE_H_

#include "Tracer.h"
#include "World.h"
#include "Light.h"
#include "Material.h"
#include "TracerUtils.h"

class TracerSimple : public Tracer {
public:
	TracerSimple();
	virtual ~TracerSimple();

	TracerSimple(World*w);

	World*world;

	RGBColor getColor(Ray ray);
};

#endif /* TRACERSIMPLE_H_ */

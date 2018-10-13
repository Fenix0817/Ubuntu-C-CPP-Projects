/*
 * TracerSimple.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#include "TracerSimple.h"

TracerSimple::TracerSimple() {
	// TODO Auto-generated constructor stub

}

TracerSimple::~TracerSimple() {
	// TODO Auto-generated destructor stub
}

void TracerSimple::create() {
}

RGBColor TracerSimple::traceRay(Ray&ray){
	ShadeInfo si = intersect(world, ray);
	si.world=world;
	si.ray = &ray;
	si.hitPoint=ray.pos+ray.dir*si.t;
	if(si.hit)return si.object->material->shade(si);
//	return Colors::white;
	return world->ambientLight->getColor(si);
}

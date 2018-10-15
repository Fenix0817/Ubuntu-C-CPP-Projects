/*
 * TracerSimple.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "TracerSimple.h"

TracerSimple::TracerSimple() {
	// TODO Auto-generated constructor stub

}

TracerSimple::~TracerSimple() {
	// TODO Auto-generated destructor stub
}

TracerSimple::TracerSimple(World*w){
	world=w;
}

RGBColor TracerSimple::getColor(Ray ray){
	ShadeInfo si=intersectWorld(world,ray);
	if(!si.hit)return world->ambient->getColor(si);
	return si.object->material->shade(si);
}

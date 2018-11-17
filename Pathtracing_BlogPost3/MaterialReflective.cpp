/*
 * MaterialReflective.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "MaterialReflective.h"


MaterialReflective::~MaterialReflective() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialReflective::shade(ShadeInfo&si){
	return Colors::black;
}
RGBColor MaterialReflective::giShade(ShadeInfo&si){
	RGBColor L=Colors::black;
	Vector3 wo=-si.ray.dir;
	Vector3 wi;
	float pdf;
	RGBColor fr=reflective->sampleF(si,wo,wi,pdf);
	Vector3 hitPoint=si.ray.pos+si.ray.dir*si.t;
	Ray reflectedRay(hitPoint,wi);
	L+=
//			fr*
			si.world->tracer->getColor(reflectedRay,si.depth+1)
//			*dotVectors(si.normal,wi)
			;
	return L;
}

/*
 * TracerGI.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "TracerGI.h"

TracerGI::TracerGI() {
	// TODO Auto-generated constructor stub

}

TracerGI::~TracerGI() {
	// TODO Auto-generated destructor stub
}

RGBColor TracerGI::getColor(Ray ray,int depth){
	if(depth>world->maxDepth)return world->bgColor;
	ShadeInfo si=intersectWorld(world,ray);
	si.depth=depth;
	if(si.hit)return si.object->material->giShade(si);
	return world->bgColor;//background
//	return Colors::red;
}

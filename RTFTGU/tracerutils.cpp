/*
 * tracerutils.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#include "tracerutils.h"

ShadeInfo intersect(World*world, Ray&ray){
	ShadeInfo si;
	si.hit=false;
	for(Object*obj:world->objects){
		ShadeInfo nsi=obj->hit(ray);
		nsi.object=obj;
		if(nsi.hit){
			if(!si.hit)si=nsi;
			else {
				if(si.t>nsi.t)si=nsi;
			}
		}
	}
	return si;
}

bool shadowIntersect(World*world,Ray&ray){
	for(Object*obj:world->objects){
		if(obj->shadowHit(ray))return true;
	}
	return false;
}

/*
 * TracerUtils.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef TRACERUTILS_H_
#define TRACERUTILS_H_

#include "Object.h"
#include <vector>
#include "World.h"

inline ShadeInfo closestShadeInfo(ShadeInfo a,ShadeInfo b){
	if(!a.hit)return b;
	if(!b.hit)return a;
	if(a.t<b.t)return a;
	return b;
}

inline ShadeInfo intersectWorld(World*w,Ray r){
	ShadeInfo si;
	si.hit=false;
	for(Object*obj:w->objects){
		ShadeInfo nsi=obj->hit(r);
		nsi.object=obj;
		si=closestShadeInfo(si,nsi);
	}
	si.world=w;
	si.ray=r;
	return si;
}

inline bool intersectShadowWorld(World*w,Ray r){
	for(Object*o:w->objects){
		if(o->shadowHit(r))return true;
	}
	return false;
}

#endif /* TRACERUTILS_H_ */

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

ShadeInfo closestShadeInfo(ShadeInfo a,ShadeInfo b){
	if(!a.hit)return b;
	if(!b.hit)return a;
	if(a.t<b.t)return a;
	return b;
}

ShadeInfo intersectWorld(World w,Ray r){
	ShadeInfo si;
	si.hit=false;
	for(Object*obj:w.objects){
		si=closestShadeInfo(si,obj->hit(r));
	}
	return si;
}

#endif /* TRACERUTILS_H_ */

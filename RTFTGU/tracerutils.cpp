/*
 * tracerutils.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#include "tracerutils.h"

ShadeInfo intersect(std::vector<Object*>&list, Ray&ray){
	ShadeInfo si;
	si.hit=false;
	for(Object*obj:list){
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

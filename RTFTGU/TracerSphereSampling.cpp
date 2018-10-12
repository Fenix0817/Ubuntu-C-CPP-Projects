/*
 * TracerSphereSampling.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#include "TracerSphereSampling.h"

TracerSphereSampling::TracerSphereSampling() {
	// TODO Auto-generated constructor stub

}

TracerSphereSampling::~TracerSphereSampling() {
	// TODO Auto-generated destructor stub
}

void TracerSphereSampling::create(){
	for(int i=0;i<10000;i++){
		Vector3 v=Vector3(randomFloat(),randomFloat(),randomFloat())*2.0f-1.0f;
		v=normalizeVector(v);
		world.push_back(new Sphere(0.03,v));
	}
}
RGBColor TracerSphereSampling::traceRay(Ray&ray){
//	ShadeInfo si = intersect(world, ray);
	float f=1;
	for(int i=0;i<world.size();i++){
		if(world[i]->hit(ray).hit){
			f-=0.1;
		}
	}
	return RGBColor(f);
}

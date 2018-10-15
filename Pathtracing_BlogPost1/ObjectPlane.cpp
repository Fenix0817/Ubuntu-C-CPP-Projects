/*
 * ObjectPlane.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "ObjectPlane.h"

ObjectPlane::ObjectPlane() {
	// TODO Auto-generated constructor stub

}

ObjectPlane::~ObjectPlane() {
	// TODO Auto-generated destructor stub
}

ObjectPlane::ObjectPlane(Vector3 p,Vector3 n){
	pos=p;
	normal=normalizeVector(n);
}

ShadeInfo ObjectPlane::hit(Ray ray){
	float t=dotVectors(pos-ray.pos,normal)/dotVectors(ray.dir,normal);
	ShadeInfo si;
	si.hit=false;
	if(t>0.0001){
		si.hit=true;
		si.normal=normal;
		si.t=t;
		si.ray=ray;
	}
	return si;
}

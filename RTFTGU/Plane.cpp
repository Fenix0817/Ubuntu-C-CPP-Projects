/*
 * Plane.cpp
 *
 *  Created on: Sep 29, 2018
 *      Author: jack
 */

#include "Plane.h"

Plane::Plane() {
	// TODO Auto-generated constructor stub

}

Plane::Plane(Vector3 p,Vector3 n){
	point=p;
	normal=normalizeVector(n);
}

Plane::Plane(Material*mat,Vector3 p,Vector3 n){
	material=mat;
	point=p;
	normal=normalizeVector(n);
}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

ShadeInfo Plane::hit(Ray ray){
	float t=dotVector(point-ray.pos,normal)/dotVector(ray.dir,normal);
	ShadeInfo si;
	si.hit=false;
	if(t>0.0001){
		si.hit=true;
		si.normal=normal;
		si.t=t;
	}
	return si;
}

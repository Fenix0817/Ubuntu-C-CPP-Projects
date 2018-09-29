/*
 * Sphere.cpp
 *
 *  Created on: Sep 28, 2018
 *      Author: jack
 */

#include "Sphere.h"

Sphere::Sphere() {
	// TODO Auto-generated constructor stub

}

Sphere::Sphere(float r,Vector3 c){
	rad=r;
	center=c;
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

ShadeInfo Sphere::hit(Ray ray){
	float a = squareLength(ray.dir);
	float b = 2*dotVector(ray.pos-center,ray.dir);
	float c = squareLength(ray.pos-center)-rad*rad;
	float t1;
	float t2;
	ShadeInfo si;
	//This check is less expensive, no square roots
	if(!solvableQuadratic(a,b,c)){
		si.hit=false;
		return si;
	}
	solveQuadratic(a,b,c,t1,t2);
	float t=min(t1,t2);
	si.hit=true;
	si.t=t;
	si.normal=normalizeVector(ray.pos+t*ray.dir-center);
	return si;
}

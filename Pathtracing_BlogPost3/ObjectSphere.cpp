/*
 * ObjectSphere.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "ObjectSphere.h"

ObjectSphere::ObjectSphere() {
	// TODO Auto-generated constructor stub

}

ObjectSphere::~ObjectSphere() {
	// TODO Auto-generated destructor stub
}

ObjectSphere::ObjectSphere(Vector3 c,float r){
	center=c;
	radius=r;
}

ShadeInfo ObjectSphere::hit(Ray ray){
	float a=squareLength(ray.dir);
	float b=2*dotVectors(ray.pos-center,ray.dir);
	float c=squareLength(ray.pos-center)-radius*radius;
	float t1;
	float t2;
	ShadeInfo si;
	si.hit=false;
//	printf("%f\n",b*b-4*a*c);
	if(!solvableQuadratic(a,b,c))return si;
//	printf("ObjectSphere::hit\n");
	solveQuadratic(a,b,c,t1,t2);
	float t=min(t1,t2);
//	if(t<0)return si;
	si.hit=true;
	si.t=t;
	si.normal=normalizeVector(ray.pos+t*ray.dir-center);
	return si;
}

/*
 * ObjectSphere.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#include "ObjectSphere.h"

ObjectSphere::ObjectSphere() {
	// TODO Auto-generated constructor stub

}

ObjectSphere::~ObjectSphere() {
	// TODO Auto-generated destructor stub
}

HitRes ObjectSphere::hit(Ray r){
	float a=dot2(r.dir);
	float b=2*dot(r.pos-pos,r.dir);
	float c=dot2(r.pos-pos)-rad*rad;
	float t1;
	float t2;
	HitRes h;
	h.h=false;
	if(b*b-4*a*c<0)return h;
	float d=sqrt(b*b-4*a*c);
	t1=(-b+d)/(2*a);
	t2=(-b-d)/(2*a);
	h.h=true;
	h.t=min(t1,t2);
	h.n=normalize(r.pos+h.t*r.dir-pos);
	return h;
}

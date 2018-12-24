/*
 * TracerGI.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#include "TracerGI.h"

TracerGI::TracerGI() {
	// TODO Auto-generated constructor stub

}

TracerGI::~TracerGI() {
	// TODO Auto-generated destructor stub
}

inline vec3 tonemap(vec3 v){
	if(v.x>1||v.y>1||v.z>1)v/=max(v.x,max(v.y,v.z));
	return v;
}

vec3 TracerGI::getColor(int x,int y){
	Ray ray=camera->getRay(vec2(x,y));
	HitRes h=(new ObjectSphere(2,vec3(0,0,0)))->hit(ray);
//	assert(normalize(h.n)==h.n);
	if(h.h)return tonemap(0.1f+2.0f*dot(-normalize(ray.pos+ray.dir*h.t-vec3(3,1,0)),h.n)*(0.5f+0.5f*h.n));
	return vec3(0,0,0);
}

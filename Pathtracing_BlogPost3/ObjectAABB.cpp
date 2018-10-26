/*
 * ObjectAABB.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "ObjectAABB.h"

ObjectAABB::ObjectAABB() {
	// TODO Auto-generated constructor stub

}

ObjectAABB::~ObjectAABB() {
	// TODO Auto-generated destructor stub
}

ObjectAABB::ObjectAABB(Vector3 min,Vector3 max){
	mi=min;
	ma=max;
}

ShadeInfo ObjectAABB::hit(Ray ray){
	ShadeInfo si;
	si.hit=false;

	float t;

	float tmin=(mi.x-ray.pos.x)/ray.dir.x;
	float tmax=(ma.x-ray.pos.x)/ray.dir.x;

	if(tmin>tmax)swap(tmin,tmax);

	float tymin=(mi.y-ray.pos.y)/ray.dir.y;
	float tymax=(ma.y-ray.pos.y)/ray.dir.y;

	if(tymin>tymax)swap(tymin,tymax);

	if(tmin>tymax||tymin>tmax){
		return si;
	}

	if(tymin>tmin){
		tmin=tymin;
	}

	if(tymax<tmax){
		tmax=tymax;
	}

	float tzmin=(mi.z-ray.pos.z)/ray.dir.z;
	float tzmax=(ma.z-ray.pos.z)/ray.dir.z;

	if(tzmin>tzmax)swap(tzmin,tzmax);

	if(tmin>tzmax||tzmin>tmax){
		return si;
	}

	if(tzmin>tmin){
		tmin=tzmin;
	}

	if(tzmax<tmax){
		tmax=tzmax;
	}

	t=tmin;

	if(t<0){
		t=tmax;
		if(t<0)return si;
	}

	si.t=t;

	Vector3 end=ray.pos+(si.t-0.0001f)*ray.dir;
	if(end.x<mi.x)si.normal=Vector3(-1,0,0);
	if(end.x>ma.x)si.normal=Vector3( 1,0,0);
	if(end.y<mi.y)si.normal=Vector3(0,-1,0);
	if(end.y>ma.y)si.normal=Vector3(0, 1,0);
	if(end.z<mi.z)si.normal=Vector3(0,0,-1);
	if(end.z>ma.z)si.normal=Vector3(0,0, 1);
	si.ray=ray;
	si.hit=true;

	return si;
}

bool ObjectAABB::shadowHit(Ray r){
	return hit(r).hit;
}

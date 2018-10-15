/*
 * ObjectDisk.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "ObjectDisk.h"

ObjectDisk::ObjectDisk() {
	// TODO Auto-generated constructor stub

}

ObjectDisk::~ObjectDisk() {
	// TODO Auto-generated destructor stub
}

ObjectDisk::ObjectDisk(Vector3 c,Vector3 n,float r){
	center=c;
	normal=normalizeVector(n);
	radius=r;
}

ShadeInfo ObjectDisk::hit(Ray ray){
	float t=dotVectors(center-ray.pos,normal)/dotVectors(ray.dir,normal);
	ShadeInfo si;
	si.hit=false;
	Vector3 p=ray.pos+t*ray.dir;
	if(squareLength(center-p)<radius*radius){
		si.hit=true;
		si.normal=normal;
		si.ray=ray;
		si.t=t;
	}
	return si;
}

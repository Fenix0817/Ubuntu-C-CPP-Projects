/*
 * TracerSimple.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: jack
 */

#include "TracerSimple.h"

TracerSimple::TracerSimple() {
	// TODO Auto-generated constructor stub

}

TracerSimple::~TracerSimple() {
	// TODO Auto-generated destructor stub
}

void TracerSimple::create() {
	Matte*matGround=new Matte();
	matGround->setAmbient(1,Colors::white);
	matGround->setDiffuse(1,Colors::white);
	MaterialPhong*matObject=new MaterialPhong();
	matObject->setAmbient(1,Colors::white);
	matObject->setDiffuse(1,Colors::green);
	matObject->setSpecular(0.75,0.5f*Colors::green+0.5f*Colors::blue,40);
	world.push_back(new Plane(matGround,Vector3(0), Vector3(0,1,0)));
	world.push_back(new Sphere(matObject,1, Vector3(0,0.5,0)));

	lights.push_back(new LightPoint(1.8f,Colors::white,Vector3(1,2,1)));

	ambient=new LightAmbient(0.2,Colors::red);
}

RGBColor TracerSimple::traceRay(Ray&ray){
	ShadeInfo si = intersect(world, ray);
	si.lights = lights;
	si.ambient = ambient;
	si.ray = &ray;
	si.hitPoint=ray.pos+ray.dir*si.t;
	if(si.hit)return si.object->material->shade(si);
//	return Colors::white;
	return ambient->getColor(si);
}

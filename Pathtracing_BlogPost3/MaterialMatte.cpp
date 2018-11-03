/*
 * MaterialMatte.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "MaterialMatte.h"

MaterialMatte::MaterialMatte() {
	// TODO Auto-generated constructor stub
	ambient=new BRDFLambertian();
	diffuse=new BRDFLambertian();
	ambient->intensity=0;
	ambient->color=Colors::black;
	diffuse->intensity=0;
	diffuse->color=Colors::black;
}

MaterialMatte::~MaterialMatte() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialMatte::shade(ShadeInfo&si){
	Vector3 wo=-si.ray.dir;
	RGBColor col=ambient->rho(si,wo)*si.world->ambient->getColor(si);
	for(Light*light:si.world->lights){
		Vector3 wi=light->getDirection(si);
		float dot=dotVectors(wi,si.normal);
		if(dot>0){
			col+=diffuse->f(si,wo,wi)*light->getColor(si)*dot;
		}
	}
	return col;
}

RGBColor MaterialMatte::giShade(ShadeInfo&si){
	Vector3 wi;
	Vector3 wo=-si.ray.dir;
	float pdf;
	RGBColor f=diffuse->sampleF(si,wi,wo,pdf);
	float ndotwi=dotVectors(si.normal,wi);
	Vector3 hitPoint=si.ray.pos+si.ray.dir*si.t;
	Ray reflectedRay(hitPoint,wi);
	return f*si.world->tracer->getColor(reflectedRay,si.depth+1)*ndotwi/pdf;
}

void MaterialMatte::setAmbient(float i,RGBColor c){
	ambient->intensity=i;
	ambient->color=c;
}

void MaterialMatte::setDiffuse(float i,RGBColor c){
	diffuse->intensity=i;
	diffuse->color=c;
}

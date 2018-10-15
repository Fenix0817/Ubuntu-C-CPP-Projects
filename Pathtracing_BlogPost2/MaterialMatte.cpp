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
	ambient->kd=0;
	ambient->cd=Colors::black;
	diffuse->kd=0;
	diffuse->cd=Colors::black;
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

void MaterialMatte::setAmbient(float i,RGBColor c){
	ambient->kd=i;
	ambient->cd=c;
}

void MaterialMatte::setDiffuse(float i,RGBColor c){
	diffuse->kd=i;
	diffuse->cd=c;
}

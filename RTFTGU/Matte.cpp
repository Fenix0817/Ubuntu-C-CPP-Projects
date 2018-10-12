/*
 * Matte.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jack
 */

#include "Matte.h"

Matte::Matte() {
	ambient = new BRDFLambertian();
	diffuse = new BRDFLambertian();
	ambient->kd=0;
	ambient->cd=Colors::white;
	diffuse->kd=0;
	diffuse->cd=Colors::white;
}

Matte::~Matte() {
	// TODO Auto-generated destructor stub
}

RGBColor Matte::shade(ShadeInfo&si){
	Vector3 wo=-si.ray->dir;
	RGBColor col=ambient->rho(si,wo)*si.ambient->getColor(si);
	for(int i=0;i<si.lights.size();i++){
		Vector3 wi=si.lights[i]->getDirection(si);
		float dot=dotVector(wi,si.normal);
		if(dot>0){
//			printf("hi %f  %f,%f,%f %f,%f,%f",dot,dir.x,dir.y,dir.z,si.lights[i]->getColor(si).x,si.lights[i]->getColor(si).y,si.lights[i]->getColor(si).z);
//			printf(" %f,%f,%f\n",(si.lights[i]->getColor(si)*dot).x,(si.lights[i]->getColor(si)*dot).y,(si.lights[i]->getColor(si)*dot).z);
			col+=diffuse->f(si,wo,wi)*si.lights[i]->getColor(si)*dot;
		}
	}
	return col;
}

void Matte::setAmbient(float i,RGBColor c){
	ambient->kd=i;
	ambient->cd=c;
}

void Matte::setDiffuse(float i,RGBColor c){
	diffuse->kd=i;
	diffuse->cd=c;
}

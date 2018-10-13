/*
 * MaterialPhong.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: jack
 */

#include "MaterialPhong.h"

MaterialPhong::MaterialPhong() {
	ambient = new BRDFLambertian();
	diffuse = new BRDFLambertian();
	specular = new BRDFGlossySpecular();
	ambient->kd=0;
	ambient->cd=Colors::white;
	diffuse->kd=0;
	diffuse->cd=Colors::white;
	specular->i=0;
	specular->ks=Colors::white;
	specular->exp=1;
}

MaterialPhong::~MaterialPhong() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialPhong::shade(ShadeInfo&si){
	Vector3 wo=-si.ray->dir;
	RGBColor col=ambient->rho(si,wo)*si.world->ambientLight->getColor(si);
	for(int i=0;i<si.world->lights.size();i++){
		Vector3 wi=si.world->lights[i]->getDirection(si);
		float dot=dotVector(wi,si.normal);
		if(dot>0){
//			printf("hi %f  %f,%f,%f %f,%f,%f",dot,dir.x,dir.y,dir.z,si.lights[i]->getColor(si).x,si.lights[i]->getColor(si).y,si.lights[i]->getColor(si).z);
//			printf(" %f,%f,%f\n",(si.lights[i]->getColor(si)*dot).x,(si.lights[i]->getColor(si)*dot).y,(si.lights[i]->getColor(si)*dot).z);
			col+=(diffuse->f(si,wo,wi)+specular->f(si,wo,wi))*si.world->lights[i]->getColor(si)*dot;
		}
	}
	return col;
}


void MaterialPhong::setAmbient(float i,RGBColor c){
	ambient->kd=i;
	ambient->cd=c;
}

void MaterialPhong::setDiffuse(float i,RGBColor c){
	diffuse->kd=i;
	diffuse->cd=c;
}

void MaterialPhong::setSpecular(float i,RGBColor c,float exp){
	specular->i=i;
	specular->ks=c;
	specular->exp=exp;
}

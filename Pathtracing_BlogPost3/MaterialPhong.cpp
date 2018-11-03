/*
 * MaterialPhong.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "MaterialPhong.h"


MaterialPhong::~MaterialPhong() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialPhong::shade(ShadeInfo&si){
	Vector3 wo=-si.ray.dir;
	RGBColor L=ambient->rho(si,wo)*si.world->ambient->getColor(si);
	for(int i=0;i<si.world->lights.size();i++){
		Vector3 wi=si.world->lights[i]->getDirection(si);
		float ndotwi=dotVectors(si.normal,wi);
		if(ndotwi>0){
			L+=(diffuse->f(si,wo,wi)+specular->f(si,wo,wi)*si.world->lights[i]->getColor(si))*ndotwi;
		}
	}
	return L;
}
RGBColor MaterialPhong::giShade(ShadeInfo&si){
	return Colors::black;
}

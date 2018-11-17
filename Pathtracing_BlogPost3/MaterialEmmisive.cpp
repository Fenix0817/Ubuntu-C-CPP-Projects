/*
 * MaterialEmmisive.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "MaterialEmmisive.h"

MaterialEmmisive::MaterialEmmisive() {
	// TODO Auto-generated constructor stub

}

MaterialEmmisive::~MaterialEmmisive() {
	// TODO Auto-generated destructor stub
}

RGBColor MaterialEmmisive::shade(ShadeInfo&si){
	return intensity*color;
}
RGBColor MaterialEmmisive::giShade(ShadeInfo&si){
//	if(-dotVectors(si.normal,si.ray.dir)>0){
//		return intensity*color;
//	}
	return intensity*color;
}

/*
 * BRDFLambertian.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: jack
 */

#include "BRDFLambertian.h"

BRDFLambertian::BRDFLambertian() {
	// TODO Auto-generated constructor stub

}

BRDFLambertian::~BRDFLambertian() {
	// TODO Auto-generated destructor stub
}


BRDFLambertian::BRDFLambertian(float k,RGBColor c){
	kd=k;
	cd=c;
}

RGBColor BRDFLambertian::f(ShadeInfo&si,Vector3&wi,Vector3&wo){
	return kd*cd*ONE_OVER_PI;
}
RGBColor BRDFLambertian::sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo){
	return kd*cd/dotVector(wi,si.normal);
}
RGBColor BRDFLambertian::rho(ShadeInfo&si,Vector3&wo){
	return kd*cd;
}

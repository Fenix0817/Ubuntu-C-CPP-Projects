/*
 * BRDFPerfectSpecular.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "BRDFPerfectSpecular.h"

BRDFPerfectSpecular::BRDFPerfectSpecular() {
	// TODO Auto-generated constructor stub

}

BRDFPerfectSpecular::~BRDFPerfectSpecular() {
	// TODO Auto-generated destructor stub
}

RGBColor BRDFPerfectSpecular::f(ShadeInfo&si,Vector3&wi,Vector3&wo){
	return Colors::black;
}
RGBColor BRDFPerfectSpecular::sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf){
	float ndotwi=dotVectors(si.normal,wo);
	wi=-wo+2.0f*si.normal*ndotwi;
	pdf=dotVectors(si.normal,wi);
	return intensity*color;
}
RGBColor BRDFPerfectSpecular::rho(ShadeInfo&si,Vector3&wo){
	return Colors::black;
}


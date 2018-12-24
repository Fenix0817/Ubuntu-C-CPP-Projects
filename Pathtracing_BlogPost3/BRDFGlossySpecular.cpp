/*
 * BRDFGlossySpecular.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#include "BRDFGlossySpecular.h"

BRDFGlossySpecular::BRDFGlossySpecular() {
	// TODO Auto-generated constructor stub

}

BRDFGlossySpecular::~BRDFGlossySpecular() {
	// TODO Auto-generated destructor stub
}

RGBColor BRDFGlossySpecular::f(ShadeInfo&si,Vector3&wi,Vector3&wo){
	float ndotwi=dotVectors(si.normal,wi);
	Vector3 r=-wi+2.0f*si.normal*ndotwi;
	float rdotwo=dotVectors(r,wo);
	if(rdotwo>0)return intensity*color*(float)pow(rdotwo,exp);
	return Colors::black;
}
RGBColor BRDFGlossySpecular::sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf){
	float ndotwo=dotVectors(si.normal,wo);
	wi=-wo+2.0f*si.normal*ndotwo;
	pdf=1;
	return intensity*color/dotVectors(si.normal,wi);
}
RGBColor BRDFGlossySpecular::rho(ShadeInfo&si,Vector3&wo){
	return Colors::black;
}

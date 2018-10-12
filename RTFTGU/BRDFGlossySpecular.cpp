/*
 * BRDFGlossySpecular.cpp
 *
 *  Created on: Oct 10, 2018
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
	float dotwi=dotVector(si.normal,wi);
	Vector3 r=-wi+2.0f*si.normal*dotwi;
	float dotwo=dotVector(r,wo);
	if(dotwo>0){
		return i*ks*powf(dotwo,exp);
	}
	return Colors::black;
}

RGBColor BRDFGlossySpecular::sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo){
	float dotwi=dotVector(si.normal,wi);
	Vector3 r=-wi+2.0f*si.normal*dotwi;
	float dotwo=dotVector(r,wo);
	if(dotwo>0){
		return i*ks*powf(dotwo,exp);
	}
	return Colors::black;
}

RGBColor BRDFGlossySpecular::rho(ShadeInfo&si,Vector3&wo){
	return Colors::black;
}


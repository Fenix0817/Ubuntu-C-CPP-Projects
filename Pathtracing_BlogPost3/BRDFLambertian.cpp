/*
 * BRDFLambertian.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#include "BRDFLambertian.h"

BRDFLambertian::BRDFLambertian() {
	sampler=new SamplerRandom(2000);
	sampler->generateSamples();
	sampler->mapSamplesToHemisphere();
}

BRDFLambertian::~BRDFLambertian() {
	// TODO Auto-generated destructor stub
}

BRDFLambertian::BRDFLambertian(float k,RGBColor c){
	intensity=k;
	color=c;
	sampler=new SamplerRandom(500);
	sampler->generateSamples();
	sampler->mapSamplesToHemisphere();
}

RGBColor BRDFLambertian::f(ShadeInfo&si,Vector3&wi,Vector3&wo){
	return intensity*color*ONE_OVER_PI;
}
RGBColor BRDFLambertian::sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf){
	Vector3 w=si.normal;
	Vector3 v=crossVectors(Vector3(0.0034,1,0.0071),w);
	v=normalizeVector(v);
	Vector3 u=crossVectors(v,w);
	u=normalizeVector(u);

	Vector3 sp=sampler->sampleHemisphere();
	wi=sp.x*u+sp.y*v+sp.z*w;
	wi=normalizeVector(wi);
	pdf=ONE_OVER_PI*dotVectors(wi,w);

	return intensity*color*ONE_OVER_PI;
}
RGBColor BRDFLambertian::rho(ShadeInfo&si,Vector3&wo){
	return intensity*color;
}

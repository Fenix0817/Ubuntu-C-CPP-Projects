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
	sampler->mapSamplesToSphere();
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
	Vector3 u=crossVectors(Vector3(0.0034,1,0.0071),w);
	u=normalizeVector(u);
	Vector3 v=crossVectors(u,w);
	v=normalizeVector(v);

	Vector3 sp=sampler->sampleSphere();
	wi=sp.x*u+sp.y*v+sp.z*w;
//	wi=sp;
	wi=normalizeVector(wi);
//	float rand1=TWO_PI*randomFloat();
//	float rand2=randomFloat();
//	float rand2s=sqrt(rand2);
//    Vector3 newdir_diffuse=normalizeVector(u*cosf(rand1)*rand2s+v*sinf(rand1)*rand2s+w*sqrtf(1.0f-rand2));
//    wi=newdir_diffuse;
	pdf=ONE_OVER_PI*dotVectors(wi,w);

	return intensity*color*ONE_OVER_PI;
}
RGBColor BRDFLambertian::rho(ShadeInfo&si,Vector3&wo){
	return intensity*color;
}

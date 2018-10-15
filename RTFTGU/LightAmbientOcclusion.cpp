/*
 * LightAmbientOcclusion.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#include "LightAmbientOcclusion.h"

LightAmbientOcclusion::LightAmbientOcclusion() {
	// TODO Auto-generated constructor stub
}

LightAmbientOcclusion::~LightAmbientOcclusion() {
	// TODO Auto-generated destructor stub
}

LightAmbientOcclusion::LightAmbientOcclusion(float i,RGBColor c,float m){
	intensity=i;
	color=c;
	minAmount=m;
	sampler=new SamplerRandom(10000);
	sampler->generateSamples();
	sampler->mapSamplesToHemisphere();
}

Vector3 LightAmbientOcclusion::getDirection(ShadeInfo&si){
//	float theta=TWO_PI*randomFloat();
//	float phi=PI*randomFloat();
//	Vector3 sampled=normalizeVector(Vector3(randomFloat(),randomFloat(),randomFloat())*2.0f-1.0f);
//	Vector3 sampled=Vector3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
	Vector3 sampled=sampler->sampleHemisphere();
	return  normalizeVector(sampled.x*u+sampled.y*v+sampled.z*w);
//	return sampled;
//	return normalizeVector(si.hitPoint-Vector3(3));
}

RGBColor LightAmbientOcclusion::getColor(ShadeInfo&si){
	if(!si.hit)return intensity*color;
	w=si.normal;
	v=crossVector(w,Vector3(0.0072,1,0.0034));
	v=normalizeVector(v);
	u=crossVector(v,w);

	Ray shadowRay;
	shadowRay.pos=si.hitPoint;
	shadowRay.dir=getDirection(si);

	if(shadowIntersect(si.world,shadowRay)){
		return minAmount*intensity*color;
	}
	return intensity*color;
}

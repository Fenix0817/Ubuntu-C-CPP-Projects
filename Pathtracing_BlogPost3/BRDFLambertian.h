/*
 * BRDFLambertian.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef BRDFLAMBERTIAN_H_
#define BRDFLAMBERTIAN_H_

#include "BRDF.h"
#include "Sampler.h"
#include "SamplerRandom.h"

class BRDFLambertian : public BRDF {
public:
	BRDFLambertian();
	virtual ~BRDFLambertian();

	BRDFLambertian(float k,RGBColor c);

	Sampler*sampler;

	RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf);
	RGBColor rho(ShadeInfo&si,Vector3&wo);

	float intensity;
	RGBColor color;
};

#endif /* BRDFLAMBERTIAN_H_ */

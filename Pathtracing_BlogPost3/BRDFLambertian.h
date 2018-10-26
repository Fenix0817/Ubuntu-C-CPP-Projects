/*
 * BRDFLambertian.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef BRDFLAMBERTIAN_H_
#define BRDFLAMBERTIAN_H_

#include "BRDF.h"

class BRDFLambertian : public BRDF {
public:
	BRDFLambertian();
	virtual ~BRDFLambertian();

	BRDFLambertian(float k,RGBColor c);

	RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor rho(ShadeInfo&si,Vector3&wo);

	float kd;
	RGBColor cd;
};

#endif /* BRDFLAMBERTIAN_H_ */

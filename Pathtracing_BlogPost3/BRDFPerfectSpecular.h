/*
 * BRDFPerfectSpecular.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef BRDFPERFECTSPECULAR_H_
#define BRDFPERFECTSPECULAR_H_

#include "BRDF.h"

class BRDFPerfectSpecular : public BRDF {
public:
	BRDFPerfectSpecular();
	virtual ~BRDFPerfectSpecular();

	float intensity;
	RGBColor color;

	BRDFPerfectSpecular(float i,RGBColor c){
		intensity=i;
		color=c;
	}

	RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf);
	RGBColor rho(ShadeInfo&si,Vector3&wo);
};

#endif /* BRDFPERFECTSPECULAR_H_ */

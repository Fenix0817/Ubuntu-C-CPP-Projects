/*
 * BRDFGlossySpecular.h
 *
 *  Created on: Oct 26, 2018
 *      Author: jack
 */

#ifndef BRDFGLOSSYSPECULAR_H_
#define BRDFGLOSSYSPECULAR_H_

#include "BRDF.h"

class BRDFGlossySpecular : public BRDF {
public:
	BRDFGlossySpecular();
	virtual ~BRDFGlossySpecular();

	float intensity;
	RGBColor color;
	float exp;

	BRDFGlossySpecular(float i,RGBColor c,float e){
		intensity=i;
		color=c;
		exp=e;
	}

	RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo,float&pdf);
	RGBColor rho(ShadeInfo&si,Vector3&wo);
};

#endif /* BRDFGLOSSYSPECULAR_H_ */

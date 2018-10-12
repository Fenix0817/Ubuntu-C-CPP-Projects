/*
 * BRDFGlossySpecular.h
 *
 *  Created on: Oct 10, 2018
 *      Author: jack
 */

#ifndef BRDFGLOSSYSPECULAR_H_
#define BRDFGLOSSYSPECULAR_H_

#include "BRDF.h"
#include "utils.h"

class BRDFGlossySpecular : public BRDF {
public:
	BRDFGlossySpecular();
	virtual ~BRDFGlossySpecular();

	RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo);
	RGBColor rho(ShadeInfo&si,Vector3&wo);

	float i;
	RGBColor ks;
	float exp;

};

#endif /* BRDFGLOSSYSPECULAR_H_ */

/*
 * BRDF.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef BRDF_H_
#define BRDF_H_

#include "Math.h"
#include "ShadeInfo.h"

class BRDF {
public:
	BRDF();
	virtual ~BRDF();

	virtual RGBColor f(ShadeInfo&si,Vector3&wi,Vector3&wo)=0;
	virtual RGBColor sampleF(ShadeInfo&si,Vector3&wi,Vector3&wo)=0;
	virtual RGBColor rho(ShadeInfo&si,Vector3&wo)=0;
};

#endif /* BRDF_H_ */

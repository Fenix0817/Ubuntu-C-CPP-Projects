/*
 * Light.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Math.h"
#include "ShadeInfo.h"

class Light {
public:
	Light();
	virtual ~Light();

	virtual Vector3 getDirection(ShadeInfo&si)=0;
	virtual RGBColor getColor(ShadeInfo&si)=0;
	virtual bool castsShadows()=0;
	virtual bool inShadow(Ray&ray,ShadeInfo&si)=0;
};

#endif /* LIGHT_H_ */

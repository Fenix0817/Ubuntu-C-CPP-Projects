/*
 * LightDirectional.h
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#ifndef LIGHTDIRECTIONAL_H_
#define LIGHTDIRECTIONAL_H_

#include "Light.h"

class LightDirectional : public Light {
public:
	LightDirectional();
	virtual ~LightDirectional();

	LightDirectional(float i,RGBColor c,Vector3 d);

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);

	float intensity;
	RGBColor color;
	Vector3 dir;
};

#endif /* LIGHTDIRECTIONAL_H_ */

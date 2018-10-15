/*
 * LightAmbient.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef LIGHTAMBIENT_H_
#define LIGHTAMBIENT_H_

#include "Light.h"

class LightAmbient : public Light {
public:
	LightAmbient();
	virtual ~LightAmbient();

	LightAmbient(float i,RGBColor c);

	float intensity;
	RGBColor color;

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);
};

#endif /* LIGHTAMBIENT_H_ */

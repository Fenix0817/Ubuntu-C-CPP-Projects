/*
 * LightAmbient.h
 *
 *  Created on: Oct 9, 2018
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

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);

	float intensity;
	RGBColor color;
};

#endif /* LIGHTAMBIENT_H_ */

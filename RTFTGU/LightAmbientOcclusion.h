/*
 * LightAmbientOcclusion.h
 *
 *  Created on: Oct 11, 2018
 *      Author: jack
 */

#ifndef LIGHTAMBIENTOCCLUSION_H_
#define LIGHTAMBIENTOCCLUSION_H_

#include "Light.h"
#include "Ray.h"
#include "tracerutils.h"

#define samples 400

class LightAmbientOcclusion : public Light {
public:
	LightAmbientOcclusion();
	virtual ~LightAmbientOcclusion();

	LightAmbientOcclusion(float i,RGBColor c,float m);

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);

	float minAmount;

	float intensity;
	RGBColor color;

private:
	Vector3 u;
	Vector3 v;
	Vector3 w;
};

#endif /* LIGHTAMBIENTOCCLUSION_H_ */

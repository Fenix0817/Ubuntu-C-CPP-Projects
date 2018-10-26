/*
 * LightDirectional.h
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#ifndef LIGHTDIRECTIONAL_H_
#define LIGHTDIRECTIONAL_H_

#include "Light.h"
#include "TracerUtils.h"

class LightDirectional : public Light {
public:
	LightDirectional();
	virtual ~LightDirectional();

	LightDirectional(float i,RGBColor c,Vector3 d);

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);
	inline bool castsShadows(){
		return true;
	}
	bool inShadow(Ray&ray,ShadeInfo&si){
		return intersectShadowWorld(si.world,Ray(ray.pos+ray.dir*si.t+dir*0.001f,dir));
	}

	float intensity;
	RGBColor color;
	Vector3 dir;
};

#endif /* LIGHTDIRECTIONAL_H_ */

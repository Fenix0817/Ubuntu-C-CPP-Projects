/*
 * LightPoint.h
 *
 *  Created on: Oct 15, 2018
 *      Author: jack
 */

#ifndef LIGHTPOINT_H_
#define LIGHTPOINT_H_

#include "Light.h"
#include "TracerUtils.h"

class LightPoint : public Light {
public:
	LightPoint();
	virtual ~LightPoint();

	LightPoint(float i,RGBColor c,Vector3 p);

	Vector3 getDirection(ShadeInfo&si);
	RGBColor getColor(ShadeInfo&si);

	inline bool castsShadows(){
		return false;
	}
	inline bool inShadow(Ray&ray,ShadeInfo&si){
		Vector3 hitPoint=si.ray.pos+si.ray.dir*si.t;
		Vector3 dir=normalizeVector(hitPoint-pos);
		return intersectShadowWorld(si.world,Ray(hitPoint,dir));
	}

	float intensity;
	RGBColor color;
	Vector3 pos;
};

#endif /* LIGHTPOINT_H_ */

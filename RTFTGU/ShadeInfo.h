/*
 * ShadeInfo.h
 *
 *  Created on: Sep 28, 2018
 *      Author: jack
 */

#ifndef SHADEINFO_H_
#define SHADEINFO_H_

#include "utils.h"

class Material;
class Light;
class Ray;
class Object;

struct ShadeInfo {
	Normal normal;
	float t;
	bool hit;
	Ray*ray;
	Material*mat;
	Vector3 hitPoint;
	std::vector<Light*>lights;
	Light*ambient;
	Object*object;
};

#endif /* SHADEINFO_H_ */

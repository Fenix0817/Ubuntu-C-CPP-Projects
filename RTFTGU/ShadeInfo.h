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
class World;

struct ShadeInfo {
	Normal normal;
	float t;
	bool hit;
	Ray*ray;
	Vector3 hitPoint;
	World*world;
	Object*object;
};

#endif /* SHADEINFO_H_ */

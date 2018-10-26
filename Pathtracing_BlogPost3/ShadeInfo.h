/*
 * ShadeInfo.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef SHADEINFO_H_
#define SHADEINFO_H_

#include "Math.h"
#include "Ray.h"

class World;
class Object;

struct ShadeInfo {
	Ray ray;
	float t;
	bool hit;
	Vector3 normal;
	World*world;
	Object*object;
};

#endif /* SHADEINFO_H_ */

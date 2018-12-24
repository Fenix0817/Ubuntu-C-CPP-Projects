/*
 * HitRes.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef HITRES_H_
#define HITRES_H_

#include "Math.h"

struct Ray;
class Object;

struct HitRes{
	bool h;
	float t;
	vec3 n;
	Ray*r;
	Object*o;
};

#endif /* HITRES_H_ */

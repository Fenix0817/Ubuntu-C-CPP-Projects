/*
 * ObjectAABB.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef OBJECTAABB_H_
#define OBJECTAABB_H_

#include "Object.h"
#include <stdio.h>

class ObjectAABB : public Object {
public:
	ObjectAABB();
	virtual ~ObjectAABB();

	Vector3 mi;
	Vector3 ma;

	ObjectAABB(Vector3 min,Vector3 max);

	ShadeInfo hit(Ray ray);
	bool shadowHit(Ray r);
};

#endif /* OBJECTAABB_H_ */

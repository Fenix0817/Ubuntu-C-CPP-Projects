/*
 * ObjectSphere.h
 *
 *  Created on: Oct 14, 2018
 *      Author: jack
 */

#ifndef OBJECTSPHERE_H_
#define OBJECTSPHERE_H_

#include "Object.h"
#include "Math.h"

class ObjectSphere: public Object {
public:
	ObjectSphere();
	virtual ~ObjectSphere();

	Vector3 center;
	float radius;

	ObjectSphere(Vector3 c,float r);

	ShadeInfo hit(Ray ray);
};

#endif /* OBJECTSPHERE_H_ */

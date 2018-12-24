/*
 * ObjectSphere.h
 *
 *  Created on: Nov 15, 2018
 *      Author: jack
 */

#ifndef OBJECTSPHERE_H_
#define OBJECTSPHERE_H_

#include "Object.h"
#include "Ray.h"

class ObjectSphere : public Object {
public:
	ObjectSphere();
	virtual ~ObjectSphere();

	float rad;
	vec3 pos;

	inline ObjectSphere(float r,vec3 p){rad=r;pos=p;}

	HitRes hit(Ray r);

};

#endif /* OBJECTSPHERE_H_ */

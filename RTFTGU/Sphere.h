/*
 * Sphere.h
 *
 *  Created on: Sep 28, 2018
 *      Author: jack
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Object.h"

class Sphere : public Object {
public:
	Sphere();
	virtual ~Sphere();

	Vector3 center;
	float rad;

	ShadeInfo hit(Ray ray);
};

#endif /* SPHERE_H_ */

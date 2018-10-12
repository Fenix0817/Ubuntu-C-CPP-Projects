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
	Sphere(float r,Vector3 c);
	Sphere(Material*mat,float r,Vector3 c);
	virtual ~Sphere();

	Vector3 center;
	float rad;

	ShadeInfo hit(Ray ray);
};

#endif /* SPHERE_H_ */

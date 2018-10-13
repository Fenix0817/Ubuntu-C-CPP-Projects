/*
 * Plane.h
 *
 *  Created on: Sep 29, 2018
 *      Author: jack
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Object.h"

class Plane : public Object {
public:
	Plane();
	Plane(Vector3 p,Vector3 n);
	Plane(Material*mat,Vector3 p,Vector3 n);
	virtual ~Plane();

	Vector3 point;
	Normal normal;

	ShadeInfo hit(Ray ray);
	bool shadowHit(Ray&ray);

};

#endif /* PLANE_H_ */
